#include "SharpUnrealPrivatePCH.h"
#include "SharpUnreal.h"
#include "SharpFunctionLibrary.h"


void USharpFunctionLibrary::SendStringEvent(FString evt, FString data) 
{
	GLog->Logf(ELogVerbosity::Log,TEXT("[USharpFunctionLibrary] SendStringEvent %s Not Implement"),*evt);
}

void USharpFunctionLibrary::SendIntEvent(FString evt, int data)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] SendIntEvent %s Not Implement"), *evt);
}

void USharpFunctionLibrary::SendFloatEvent(FString evt, float data)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] SendFloatEvent %s Not Implement"), *evt);
}

void USharpFunctionLibrary::SetStringData(FString key, FString data)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] SetStringData %s Not Implement"), *key);
}

void USharpFunctionLibrary::SetIntData(FString key, int data)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] SetIntData %s Not Implement"), *key);
}

void USharpFunctionLibrary::SetFloatData(FString key, float data)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] SetFloatData %s Not Implement"), *key);
}

FString USharpFunctionLibrary::GetStringData(FString key)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] GetStringData %s Not Implement"), *key);
	return key;
}

int USharpFunctionLibrary::GetIntData(FString key)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] GetIntData %s Not Implement"), *key);
	return 0;
}

float USharpFunctionLibrary::GetFloatData(FString key)
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[USharpFunctionLibrary] GetFloatData %s Not Implement"), *key);
	return 0.0f;
}

