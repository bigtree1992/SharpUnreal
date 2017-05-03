#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "UnrealAPI_Physics.h"

static UPrimitiveComponent* LineTraceSingle(FVector start,FVector end, ECollisionChannel channel)
{
	FHitResult OutHit;
	if(GWorld->LineTraceSingleByChannel(OutHit,start,end,channel))
	{
		return OutHit.GetComponent();
	}
	else {
		return NULL;
	}
}


void UnrealAPI_Physics::RegisterAPI() 
{
	
}

