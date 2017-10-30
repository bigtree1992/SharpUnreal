#include "SharpUnrealPrivatePCH.h"
#include "UnrealAPI_Physics.h"

#include "Engine/EngineBaseTypes.h"
#include "Engine/World.h"

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

static FVector UnrealEngine_Physics_LineTraceSingleGetPoint(FVector start,FVector end, ECollisionChannel channel)
{
	FHitResult OutHit;
	if(GWorld->LineTraceSingleByChannel(OutHit,start,end,channel))
	{
		return OutHit.Location;
	}
	else 
	{
		return start;
	}
}

static FVector UnrealEngine_Physics_LineTraceSingleGetPointWithTag(FVector start, FVector end, ECollisionChannel channel,MonoString* tag)
{
	FHitResult OutHit;
	if (GWorld->LineTraceSingleByChannel(OutHit, start, end, channel))
	{
		FName tag_name = FName((TCHAR*)mono_string_chars(tag));
		if (OutHit.Actor->ActorHasTag(tag_name)) {
			return OutHit.Location;
		}
		else {
			return start;
		}
	}
	else
	{
		return start;
	}
}


void UnrealAPI_Physics::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.Physics::_LineTraceSingleGetPoint",
		reinterpret_cast<void*>(UnrealEngine_Physics_LineTraceSingleGetPoint));
	mono_add_internal_call("UnrealEngine.Physics::_LineTraceSingleGetPointWithTag",
		reinterpret_cast<void*>(UnrealEngine_Physics_LineTraceSingleGetPointWithTag));
}
