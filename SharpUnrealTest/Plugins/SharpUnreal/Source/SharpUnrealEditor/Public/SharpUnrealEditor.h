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

	//监控BuildLibs文件夹，进行动态热更新C#代码
	void OnRuntimeDllChanged(const TArray<FFileChangeData>& InFileChanges);
	FDelegateHandle OnDllChangedHandle;

	//监控StageBuilds文件夹，进行自动复制打包后需要的运行时库文件
	void OnStageBuildsChanged(const TArray<FFileChangeData>& InFileChanges);
	FDelegateHandle OnStageBuildsHandle;

	FDateTime LastAssemblyMotifyTimeStamp;
	bool IsEditorRunningGame;
	FString MainAssemblyPath;
};