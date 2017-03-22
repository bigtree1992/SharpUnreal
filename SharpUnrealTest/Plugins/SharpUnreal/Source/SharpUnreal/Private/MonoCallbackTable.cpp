#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "MonoCallbackTable.h"
#include "MonoRuntime.h"

#include <mono/jit/jit.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/class.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/tokentype.h>
#include <mono/utils/mono-counters.h>
#include <mono/utils/mono-logger.h>
#include <mono/metadata/mono-debug.h>

static TMap<_MonoClass*,MonoCallback*> g_CallbackTable;

void MonoCallbackTable::CreateClassCallback(_MonoClass* klass)
{
	if (g_CallbackTable.Contains(klass))
	{
		const char* name = mono_class_get_name(klass);
		GLog->Logf(ELogVerbosity::Log, TEXT("[CreateCallback] Same Name Class Find:%s,Ignored."), *FString(name));
		return;
	}

	MonoCallback* m_Callback = new MonoCallback();
	m_Callback->Clear();

	m_Callback->OnRegister = MonoRuntime::Instance()->FindMethod(klass, "OnRegister", -1);	
	m_Callback->OnUnregister = MonoRuntime::Instance()->FindMethod(klass, "OnUnregister", -1);	
	m_Callback->Initialize = MonoRuntime::Instance()->FindMethod(klass, "Initialize", -1);
	m_Callback->Uninitialize = MonoRuntime::Instance()->FindMethod(klass, "Uninitialize", -1);	
	m_Callback->BeginPlay = MonoRuntime::Instance()->FindMethod(klass, "BeginPlay", -1);
	m_Callback->EndPlay = MonoRuntime::Instance()->FindMethod(klass, "EndPlay", -1);
	m_Callback->Tick = MonoRuntime::Instance()->FindMethod(klass, "Tick", 1);
	m_Callback->OnEvent = MonoRuntime::Instance()->FindMethod(klass, "OnEvent", 1);

	m_Callback->OnAppDeactivate = MonoRuntime::Instance()->FindMethod(klass, "OnAppDeactivate", 1);
	m_Callback->OnAppHasReactivated = MonoRuntime::Instance()->FindMethod(klass, "OnAppHasReactivated", 1);
	m_Callback->OnAppWillEnterBackground = MonoRuntime::Instance()->FindMethod(klass, "OnAppWillEnterBackground", 1);
	m_Callback->OnAppHasEnteredForeground = MonoRuntime::Instance()->FindMethod(klass, "OnAppHasEnteredForeground", 1);
	m_Callback->OnAppWillTerminate = MonoRuntime::Instance()->FindMethod(klass, "OnAppWillTerminate", 1);

	m_Callback->OnComponentHit = MonoRuntime::Instance()->FindMethod(klass, "OnComponentHit", 5);
	m_Callback->OnComponentBeginOverlap = MonoRuntime::Instance()->FindMethod(klass, "OnComponentBeginOverlap", 6);
	m_Callback->OnComponentEndOverlap = MonoRuntime::Instance()->FindMethod(klass, "OnComponentEndOverlap", 4);
	m_Callback->OnComponentWake = MonoRuntime::Instance()->FindMethod(klass, "OnComponentWake", 2);
	m_Callback->OnComponentSleep = MonoRuntime::Instance()->FindMethod(klass, "OnComponentSleep", 2);
	m_Callback->OnParticleSpawn = MonoRuntime::Instance()->FindMethod(klass, "OnParticleSpawn", 4);
	m_Callback->OnParticleBurst = MonoRuntime::Instance()->FindMethod(klass, "OnParticleBurst", 3);
	m_Callback->OnParticleDeath = MonoRuntime::Instance()->FindMethod(klass, "OnParticleDeath", 6);
	m_Callback->OnParticleCollide = MonoRuntime::Instance()->FindMethod(klass, "OnParticleCollide", 9);
	m_Callback->OnSystemFinished = MonoRuntime::Instance()->FindMethod(klass, "OnSystemFinished", 1);
	m_Callback->OnAudioFinished = MonoRuntime::Instance()->FindMethod(klass, "OnAudioFinished", -1);
	m_Callback->OnAudioPlaybackPercent = MonoRuntime::Instance()->FindMethod(klass, "OnAudioPlaybackPercent", 2);
	m_Callback->OnSequencerStart = MonoRuntime::Instance()->FindMethod(klass, "OnSequencerStart", -1);
	m_Callback->OnSequencerPause = MonoRuntime::Instance()->FindMethod(klass, "OnSequencerPause", -1);
	m_Callback->OnSequencerStop = MonoRuntime::Instance()->FindMethod(klass, "OnSequencerStop", -1);


	g_CallbackTable.Add(klass,m_Callback);

	const char* name = mono_class_get_name(klass);

	GLog->Logf(ELogVerbosity::Log, TEXT("[CreateCallback] Name:%s"), *FString(name));
}

void MonoCallbackTable::DestroyAllCallback()
{
	for (auto& elem : g_CallbackTable)
	{
		if (elem.Value) 
		{
			delete elem.Value;
		}
	}
	GLog->Logf(ELogVerbosity::Log, TEXT("[DestroyAllCallbask]"));
}

MonoCallback* MonoCallbackTable::GetCallbackByClass(_MonoClass* klass)
{
	if (g_CallbackTable.Contains(klass)) 
	{
		return g_CallbackTable[klass];
	}
	else {
		return NULL;
	}
}

MonoCallback* MonoCallbackTable::GetCallbackByObject(_MonoObject* obj)
{
	MonoClass* klass = mono_object_get_class(obj);
	return GetCallbackByClass(klass);
}