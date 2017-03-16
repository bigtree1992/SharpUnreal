// Fill out your copyright notice in the Description page of Project Settings.

#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "MonoRuntime.h"
#include "Engine.h"

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
		//��������ʱ�������·��
		mono_set_assemblies_path(TCHAR_TO_ANSI(*runtime));
		//����mono���������
		s_Instance->m_RootDomain = mono_jit_init_version("SharpUnreal RootDomain", "v4.0.30319");
		GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] RootDomain Created."));
	}

	int ret = s_Instance->ReloadMainAssembly();
	if (ret != 0) 
	{
		return ret;
	}

	GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] CreateInstance Success."));

	return 0;
}

void MonoRuntime::DestoryInstance()
{
	if (s_Instance && s_Instance->m_RootDomain != NULL)
	{
		if (s_Instance->m_ChildDomain != NULL)
		{
			//unload֮ǰ�����л�����domain
			mono_domain_set(s_Instance->m_RootDomain, 0);
			mono_domain_unload(s_Instance->m_ChildDomain);
		}
		s_Instance->m_ChildDomain = NULL;
		s_Instance->m_MainAssembly = NULL;
		s_Instance->m_MainImage = NULL;
#if !WITH_EDITOR
		mono_jit_cleanup(_domain);
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

void MonoRuntime::CopyToTarget(FString &target)
{
	FString build = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::GameDir(), TEXT("BuildLibs")));

	FString source = build / TEXT("MainAssembly.dll");

	if (FPaths::FileExists(source)) 
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (FPaths::FileExists(target)) 
		{
			PlatformFile.DeleteFile(*target);
		}
		if (!PlatformFile.CopyFile(*target, *source)) 
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[MonoRuntime] CopyAssembly Failed: %s,%s."),*target,*source);
		}
	}
}

int MonoRuntime::ReloadMainAssembly()
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
		//unload֮ǰ�����л�����domain
		mono_domain_set(m_RootDomain, 0);
		mono_domain_unload(m_ChildDomain);
	}
	m_ChildDomain = mono_domain_create_appdomain("SharpUnreal ChildDomain", NULL);
	mono_domain_set(m_ChildDomain, 0);

	//���Ʋ������ļ�
	CopyToTarget(assembly_path);

	if (!FPaths::FileExists(assembly_path))
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] MainAssembly.dll NotExist."));
		return 1001;
	}

	//��������ű�Dll�ļ�
	m_EngineAssembly = mono_domain_assembly_open(mono_domain_get(), TCHAR_TO_ANSI(*engine_path));
	if (!m_EngineAssembly)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Can Not Load Assembly:UnrealEngine.dll."));
		return 1002;
	}
	//���ݼ��ص�����dll��ȡ����
	m_EngineImage = mono_assembly_get_image(m_EngineAssembly);
	if (m_EngineImage == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get UnrealEngine.dll Image Failed!!"));
		return 1003;
	}

	//�����߼��ű�Dll�ļ�
	m_MainAssembly = mono_domain_assembly_open(mono_domain_get(), TCHAR_TO_ANSI(*assembly_path));
	if (!m_MainAssembly)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Can Not Load Assembly:MainAssembly.dll."));
		return 1002;
	}
	//���ݼ��ص��߼�dll��ȡ����
	m_MainImage = mono_assembly_get_image(m_MainAssembly);
	if (m_MainImage == NULL)
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[MonoRuntime] Get MainAssembly.dll Image Failed!!"));
		return 1003;
	}

	GLog->Log(ELogVerbosity::Log, TEXT("[MonoRuntime] MainAssembly.dll Load Success."));

#if WITH_EDITOR
	//�༭��ģʽ�»�������ActorComponent����������
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
			m_ComponentNames.Add(FString(name));
		}
	}
#endif
	return 0;
}

TArray<FString> MonoRuntime::GetAllMonoComponent()
{
	return m_ComponentNames;
}

MonoRuntime::MonoRuntime()
	: m_RootDomain(NULL)
	, m_ChildDomain(NULL)
	, m_MainAssembly(NULL)
	, m_MainImage(NULL)
{}


