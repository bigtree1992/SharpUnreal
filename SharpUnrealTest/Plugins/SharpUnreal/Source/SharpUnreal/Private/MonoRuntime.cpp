// Fill out your copyright notice in the Description page of Project Settings.

#include "SharpUnrealPrivatePCH.h"
#include "Engine.h"
#include "SharpUnreal.h"
#include "MonoRuntime.h"
#include "MonoCallbackTable.h"
#include "MonoClassTable.h"

#include "UnrealAPI/UnrealAPI_Engine.h"
#include "UnrealAPI/UnrealAPI_Math.h"
#include "UnrealAPI/UnrealAPI_Component.h"
#include "UnrealAPI/UnrealAPI_GamePlay.h"
#include "UnrealAPI/UnrealAPI_Animation.h"
#include "UnrealAPI/UnrealAPI_Audio.h"
#include "UnrealAPI/UnrealAPI_Rendering.h"
#include "UnrealAPI/UnrealAPI_Movement.h"
#include "UnrealAPI/UnrealAPI_Spline.h"

#include <mono/jit/jit.h>
#include "mono/metadata/metadata.h"
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/class.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/tokentype.h>
#include <mono/utils/mono-counters.h>

static MonoRuntime* s_Instance;

int MonoRuntime::CreateInstance()
{
	FString runtime = FPaths::Combine(FPaths::GameDir(), TEXT("RuntimeLibs"));

	if (s_Instance == NULL)
	{
		s_Instance = new MonoRuntime();
		//设置运行时环境库的路径
		mono_set_assemblies_path(TCHAR_TO_ANSI(*runtime));
		//创建mono虚拟机环境
		s_Instance->m_RootDomain = mono_jit_init_version("SharpUnreal RootDomain", "v4.0.30319");
		GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] RootDomain Created."));
	}

	MonoClassTable::CreateTable();
	int ret = s_Instance->ReloadAssembly();
	if (ret != 0) 
	{
		return ret;
	}

	GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] CreateInstance Success."));

	return 0;
}

void MonoRuntime::DestoryInstance()
{
	MonoClassTable::DestroyTable();
	if (s_Instance && s_Instance->m_RootDomain != NULL)
	{
		if (s_Instance->m_ChildDomain != NULL)
		{
			//unload之前必须切换到根domain
			mono_domain_set(s_Instance->m_RootDomain, 0);
			mono_domain_unload(s_Instance->m_ChildDomain);
			MonoCallbackTable::DestroyAllCallback();
		}

		s_Instance->m_ChildDomain = NULL;
		s_Instance->m_MainAssembly = NULL;
		s_Instance->m_MainImage = NULL;
		s_Instance->m_MainAssembly = NULL;
		s_Instance->m_EngineAssembly = NULL;

#if !WITH_EDITOR
		mono_jit_cleanup(s_Instance->m_RootDomain);
#endif
		GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] CDestoryInstance."));
	}
	else
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] DestoryInstance But Null."));
	}
}

MonoRuntime* MonoRuntime::Instance()
{
	if (s_Instance == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoManager] Instance Is Null!"));
	}
	return s_Instance;
}

void MonoRuntime::CopyToTarget(const FString& source,const FString &target)
{
	FString build = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::GameDir(), TEXT("BuildLibs")));

	FString source_path = build / *source;

	if (FPaths::FileExists(source_path))
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (FPaths::FileExists(target)) 
		{
			PlatformFile.DeleteFile(*target);
		}
		if (!PlatformFile.CopyFile(*target, *source_path))
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CopyAssembly Failed: %s,%s."),*target,*source_path);
		}
	}
}

int MonoRuntime::ReloadAssembly()
{
	if (m_RootDomain == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] RootDomain Should Not Be Null."));
		return 1000;
	}

	FString runtime = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::GameDir(), TEXT("RuntimeLibs")));
	FString assembly_path = runtime / TEXT("mono") / TEXT("4.5") / TEXT("MainAssembly.dll");
	FString engine_path = runtime / TEXT("mono") / TEXT("4.5") / TEXT("UnrealEngine.dll");

	if (m_ChildDomain != NULL)
	{
		//unload之前必须切换到根domain
		mono_domain_set(m_RootDomain, 0);
		mono_domain_unload(m_ChildDomain);
		MonoCallbackTable::DestroyAllCallback();
	}
	m_ChildDomain = mono_domain_create_appdomain("SharpUnreal ChildDomain", NULL);
	mono_domain_set(m_ChildDomain, 0);

#if WITH_EDITOR
	//复制并覆盖文件
	CopyToTarget(TEXT("MainAssembly.dll"), assembly_path);
	CopyToTarget(TEXT("UnrealEngine.dll"), engine_path);
#endif
	if (!FPaths::FileExists(assembly_path))
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] MainAssembly.dll NotExist."));
		return 1001;
	}

	//加载引擎脚本Dll文件
	m_EngineAssembly = mono_domain_assembly_open(mono_domain_get(), TCHAR_TO_ANSI(*engine_path));
	if (!m_EngineAssembly)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Can Not Load Assembly:UnrealEngine.dll."));
		return 1002;
	}
	//根据加载的引擎dll获取镜像
	m_EngineImage = mono_assembly_get_image(m_EngineAssembly);
	if (m_EngineImage == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get UnrealEngine.dll Image Failed!!"));
		return 1003;
	}

	//注册C#调用C++的回调函数
	UnrealAPI_Engine::RegisterAPI();
	UnrealAPI_Math::RegisterAPI();
	UnrealAPI_Component::RegisterAPI();
	UnrealAPI_GamePlay::RegisterAPI();
	UnrealAPI_Animation::RegisterAPI();
	UnrealAPI_Audio::RegisterAPI();
	UnrealAPI_Rendering::RegisterAPI();
	UnrealAPI_Movement::RegisterAPI();
	UnrealAPI_Spline::RegisterAPI();


	//加载逻辑脚本Dll文件
	m_MainAssembly = mono_domain_assembly_open(mono_domain_get(), TCHAR_TO_ANSI(*assembly_path));
	if (!m_MainAssembly)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Can Not Load Assembly:MainAssembly.dll."));
		return 1002;
	}
	//根据加载的逻辑dll获取镜像
	m_MainImage = mono_assembly_get_image(m_MainAssembly);
	if (m_MainImage == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get MainAssembly.dll Image Failed!!"));
		return 1003;
	}
	//缓存下所有ActorComponent的子类引用
	m_ComponentNames = TArray<FString>();
	if (m_RootDomain == NULL || m_ChildDomain == NULL ||
		m_MainAssembly == NULL || m_MainImage == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get ComponentNames Failed! MainImage Is Null"));
		return 1004;
	}

	MonoClass* base = mono_class_from_name(m_EngineImage, "UnrealEngine", "ActorComponent");
	if (base == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get ComponentNames Failed! Not Find ActorComponent."));
		return 1005;
	}

	unsigned length = 0;
	int rows = mono_image_get_table_rows(m_MainImage, MONO_TABLE_TYPEDEF);
	for (int i = 1; i < rows; ++i)
	{
		MonoClass * klass = mono_class_get(m_MainImage, (i + 1) | MONO_TOKEN_TYPE_DEF);

		if (klass == NULL)
		{
			continue;
		}

		if (mono_class_is_subclass_of(klass, base, false))
		{
			const char * name = mono_class_get_name(klass);
			#if WITH_EDITOR			
			m_ComponentNames.Add(FString(name));
			#endif
			//初始化创建类的回调函数
			MonoCallbackTable::CreateClassCallback(klass);
		}
	}

	#if WITH_EDITOR			
	m_ComponentNames.Add(FString(TEXT("Timer")));
	GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] Add Timer"));
	#endif

	GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] ReloadAssembly Complete."));
	return 0;
}

TArray<FString> MonoRuntime::GetAllMonoComponent()
{
	return m_ComponentNames;
}

_MonoObject* MonoRuntime::CreateObject(const char * name)
{
	if (m_MainAssembly == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error,TEXT("[MonoRuntime] MainAssembly Is Null When CreateObject %s"),name);
		return NULL;
	}

	MonoClass* klass = mono_class_from_name(m_MainImage, "MainAssembly", name);
	if (klass == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CreateObject But Can't Find %s "), name);
		return NULL;
	}

	MonoObject* obj = mono_object_new(mono_domain_get(), klass);
	if (obj == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CreateObject Failed %s "), name);
		return NULL;
	}
	mono_runtime_object_init(obj);
	
	return obj;
}

_MonoObject* MonoRuntime::CreateObjectFromEngine(const char * name)
{
	if (m_EngineAssembly == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] m_EngineAssembly Is Null When CreateObjectFromEngine %s"), name);
		return NULL;
	}

	MonoClass* klass = mono_class_from_name(m_EngineImage, "UnrealEngine", name);
	if (klass == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CreateObjectFromEngine But Can't Find %s "), name);
		return NULL;
	}

	MonoObject* obj = mono_object_new(mono_domain_get(), klass);
	if (obj == NULL)
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CreateObjectFromEngine Failed %s "), name);
		return NULL;
	}
	mono_runtime_object_init(obj);

	return obj;
}

uint32_t MonoRuntime::RetainObject(_MonoObject* object)
{
	return mono_gchandle_new(object, 1);
}

void MonoRuntime::FreeObject(uint32_t handle)
{
	mono_gchandle_free(handle);
}

void MonoRuntime::SetNativeHandler(_MonoObject* object, void* handler)
{
	MonoClass* klass = mono_object_get_class(object);
	MonoClassField* field = mono_class_get_field_from_name(klass, "m_NativeHandler");
	mono_field_set_value(object, field, handler);
}

_MonoMethod* MonoRuntime::FindMethod(_MonoClass* klass, const char* name, int paramCount)
{
	while (klass != NULL)
	{
		MonoMethod* method = mono_class_get_method_from_name(klass, name, paramCount);
		if (method != NULL)
		{
			return method;
		}
		klass = mono_class_get_parent(klass);
	};

	return NULL;
}

_MonoMethod* MonoRuntime::FindMethodByObj(_MonoObject* object, const char* name, int paramCount)
{
	MonoClass* klass = mono_object_get_class(object);
	return FindMethod(klass, name, paramCount);
}

_MonoObject* MonoRuntime::InvokeMethod(_MonoMethod *method, void *obj, void **params)
{
	if (method == NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[InvokMethod] Method Is Null."));
		return NULL;
	}

	MonoObject * ex = NULL;
	_MonoObject* ret = mono_runtime_invoke(method, obj, params, &ex);
	if (ex != NULL) 
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("[InvokMethod] Failed!"));
		mono_print_unhandled_exception(ex);
		return NULL;
	}
	return ret;
}

_MonoClass* MonoRuntime::FindClassByName(const char* name)
{
	return mono_class_from_name(m_EngineImage, "UnrealEngine", name);
}

MonoRuntime::MonoRuntime()
	: m_RootDomain(NULL)
	, m_ChildDomain(NULL)
	, m_MainAssembly(NULL)
	, m_MainImage(NULL)
	, m_EngineAssembly(NULL)
	, m_EngineImage(NULL)
{}



