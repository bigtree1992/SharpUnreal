// Fill out your copyright notice in the Description page of Project Settings.

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

static void UnrealEngine_Log_Debug(MonoString * content)
{
	GLog->Logf(ELogVerbosity::Log, *FString(mono_string_to_utf8(content)));
}

static void UnrealEngine_Log_Error(MonoString * content)
{
	GLog->Logf(ELogVerbosity::Error, *FString(mono_string_to_utf8(content)));
}


void UnrealAPI_Engine::RegisterAPI()
{
	mono_add_internal_call("UnrealEngine.Log::Debug", reinterpret_cast<void*>(UnrealEngine_Log_Debug));
	mono_add_internal_call("UnrealEngine.Log::Error", reinterpret_cast<void*>(UnrealEngine_Log_Error));

}


