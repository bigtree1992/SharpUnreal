#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Engine.h"

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


//日志回调
extern "C" static void MonoPrintf(const char *string, mono_bool is_stdout)
{
	GLog->Logf(ELogVerbosity::Error, TEXT("%s"), ANSI_TO_TCHAR(string));
}

extern "C" static void MonoLog(const char *log_domain, const char *log_level, const char *message, mono_bool fatal, void *user_data)
{
	// logs are always a single line, so can avoid routing through log bridge
	// note: code is repeated because verbosity suppression is performed at compile-time
	if (fatal || 0 == FCStringAnsi::Strncmp("error", log_level, 5))
	{
		// fatal error
		GLog->Logf(ELogVerbosity::Fatal, TEXT("%s%s%s"), log_domain != nullptr ? ANSI_TO_TCHAR(log_domain) : TEXT(""), log_domain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(message));
	}
	else if (0 == FCStringAnsi::Strncmp("warning", log_level, 7))
	{
		GLog->Logf(ELogVerbosity::Warning, TEXT("%s%s%s"), log_domain != nullptr ? ANSI_TO_TCHAR(log_domain) : TEXT(""), log_domain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(message));
	}
	else if (0 == FCStringAnsi::Strncmp("critical", log_level, 8))
	{
		GLog->Logf(ELogVerbosity::Error, TEXT("%s%s%s"), log_domain != nullptr ? ANSI_TO_TCHAR(log_domain) : TEXT(""), log_domain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(message));
	}
	else
	{
		GLog->Logf(ELogVerbosity::Log, TEXT("%s%s%s"), log_domain != nullptr ? ANSI_TO_TCHAR(log_domain) : TEXT(""), log_domain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(message));
	}
}

//Log类函数注册
static void UnrealEngine_Log_Debug(MonoString* content)
{
	GLog->Logf(ELogVerbosity::Log, *FString(mono_string_to_utf16(content)));
}

static void UnrealEngine_Log_Warning(MonoString* content)
{
	GLog->Logf(ELogVerbosity::Log, *FString(mono_string_to_utf16(content)));
}

static void UnrealEngine_Log_Error(MonoString* content)
{
	GLog->Logf(ELogVerbosity::Error, *FString(mono_string_to_utf16(content)));
}

//World类函数注册
static MonoString* UnrealEngine_World_GetCurrentLevel() 
{	
	UWorld* world = GEngine->GetWorld();
	if (world != NULL) 
	{
		ULevel* level = world->GetCurrentLevel();
		if (level != NULL) 
		{
			const TCHAR* name = *level->GetName();
			MonoString* ret = mono_string_from_utf16((mono_unichar2*)name);
			return ret;
		}
	}
	else {
		GLog->Log(ELogVerbosity::Error, TEXT("[World] Can't GetWorld When GetCurrentLevel."));
	}
	return NULL;
}

static void UnrealEngine_World_LoadStreamingLevel(MonoString* name) 
{
	UWorld* World = GEngine->GetWorld();
	if (World != NULL)
	{
		FName LevelName((WIDECHAR*)mono_string_to_utf16(name));
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(World, LevelName,true,false,LatentInfo);

	}
	else {
		GLog->Log(ELogVerbosity::Error, TEXT("[World] Can't GetWorld When LoadStreamingLevel."));
	}
}

static void UnrealEngine_World_UnLoadStreamingLevel(MonoString* name)
{
	UWorld* World = GEngine->GetWorld();
	if (World != NULL)
	{
		FName LevelName((WIDECHAR*)mono_string_to_utf16(name));
		FLatentActionInfo LatentInfo;
		UGameplayStatics::UnloadStreamLevel(World, LevelName, LatentInfo);

	}
	else {
		GLog->Log(ELogVerbosity::Error, TEXT("[World] Can't GetWorld When UnLoadStreamingLevel."));
	}
}

static AActor* UnrealEngine_World_SpwanActor(MonoString* path, FTransform* trans)
{
	UWorld* World = GEngine->GetWorld();
	if (World == NULL) 
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[World] Can't GetWorld When SpwanActor."));
		return NULL;
	}
	
	UClass* Class = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), 
		nullptr, (const TCHAR*)mono_string_to_utf16(path)));
	if (Class == NULL) 
	{
		GLog->Log(ELogVerbosity::Error, TEXT("[World] Can't GetClass When SpwanActor."));
		return NULL;
	}

	return World->SpawnActor(Class, trans);
}



void UnrealAPI_Engine::RegisterAPI()
{
	mono_trace_set_log_handler(MonoLog, NULL);
	mono_trace_set_print_handler(MonoPrintf);
	mono_trace_set_printerr_handler(MonoPrintf);

	mono_add_internal_call("UnrealEngine.Log::Debug",
		reinterpret_cast<void*>(UnrealEngine_Log_Debug));
	mono_add_internal_call("UnrealEngine.Log::Warning", 
		reinterpret_cast<void*>(UnrealEngine_Log_Warning));
	mono_add_internal_call("UnrealEngine.Log::Error", 
		reinterpret_cast<void*>(UnrealEngine_Log_Error));

	mono_add_internal_call("UnrealEngine.World::GetCurrentLevel", 
		reinterpret_cast<void*>(UnrealEngine_World_GetCurrentLevel));
	mono_add_internal_call("UnrealEngine.World::LoadStreamingLevel",
		reinterpret_cast<void*>(UnrealEngine_World_LoadStreamingLevel));
	mono_add_internal_call("UnrealEngine.World::UnLoadStreamingLevel",
		reinterpret_cast<void*>(UnrealEngine_World_UnLoadStreamingLevel)); 
	mono_add_internal_call("UnrealEngine.World::_SpwanActor",
			reinterpret_cast<void*>(UnrealEngine_World_SpwanActor));
}


