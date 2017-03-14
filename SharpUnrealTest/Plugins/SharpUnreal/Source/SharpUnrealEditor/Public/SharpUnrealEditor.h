// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"
#include "DateTime.h"

struct FFileChangeData;

class FSharpUnrealEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Called when UnrealEd enters Play In Editor mode. */
	void OnBeginPIE(const bool bIsSimulating);
	/** Called when UnrealEd exits Play In Editor mode. */
	void OnEndPIE(const bool bIsSimulating);

	void OnBinaryDirChanged(const TArray<FFileChangeData>& InFileChanges);

	FDelegateHandle OnBinaryDirChangedDelegateHandle;

	FDateTime LastAssemblyMotifyTimeStamp;

	bool IsEditorRunningGame;

	FString MainAssemblyPath;
};