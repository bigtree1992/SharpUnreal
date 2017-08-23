#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Physics.h"

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


void UnrealAPI_Physics::RegisterAPI() 
{
	mono_add_internal_call("UnrealEngine.Physics::_LineTraceSingleGetPoint",
		reinterpret_cast<void*>(UnrealEngine_Physics_LineTraceSingleGetPoint));
}
