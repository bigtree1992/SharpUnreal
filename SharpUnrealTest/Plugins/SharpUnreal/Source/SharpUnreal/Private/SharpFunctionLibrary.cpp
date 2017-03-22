#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "SharpFunctionLibrary.h"


void USharpFunctionLibrary::SendStringEvent(FString evt, FString data) 
{
	GLog->Logf(ELogVerbosity::Log,TEXT("[USharpFunctionLibrary] SendStringEvent %s"),*evt);
}

