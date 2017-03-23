// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SharpUnrealPrivatePCH.h"
#include "MonoRuntime.h"

#define LOCTEXT_NAMESPACE "FSharpUnrealModule"

void FSharpUnrealModule::StartupModule()
{
	MonoRuntime::CreateInstance();
}

void FSharpUnrealModule::ShutdownModule()
{
	MonoRuntime::DestoryInstance();
}

void FSharpUnrealModule::ReloadMainAssembly()
{
	MonoRuntime::Instance()->ReloadAssembly();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSharpUnrealModule, SharpUnreal)