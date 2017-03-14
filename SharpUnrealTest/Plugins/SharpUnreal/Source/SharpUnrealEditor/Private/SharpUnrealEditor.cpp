// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SharpUnrealEditorPrivatePCH.h"
#include "IDirectoryWatcher.h"
#include "DirectoryWatcherModule.h"
#include "MonoComponentDetails.h"

#define LOCTEXT_NAMESPACE "FSharpUnrealEditorModule"

void FSharpUnrealEditorModule::StartupModule()
{
	GLog->Logf(ELogVerbosity::Log,TEXT("[SharpUnrealEditor] StartupModule."));
	
	//注册MonoComponent的自定义Editor
	auto& PropertyModule =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(FName("MonoComponent"),
		FOnGetDetailCustomizationInstance::CreateStatic(&FMonoComponentDetails::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
	//注册监听dll文件夹的变化
	auto& DirWatcherModule =
		FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>("DirectoryWatcher");
	auto DirWatcher = DirWatcherModule.Get();
	if (DirWatcher)
	{
		FString runtime = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("RuntimeLibs"));
		GLog->Logf(TEXT("[SharpUnrealEditor] RuntimeLibs Path %s"), *runtime);

		MainAssemblyPath = runtime / TEXT("mono") / TEXT("4.5") / "MainAssembly.dll";

		DirWatcher->RegisterDirectoryChangedCallback_Handle(
			runtime, IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FSharpUnrealEditorModule::OnBinaryDirChanged),
			OnBinaryDirChangedDelegateHandle
		);
	}
	else {
		GLog->Logf(ELogVerbosity::Error, TEXT("[SharpUnrealEditor] DirWatcher is null."));
	}

	IsEditorRunningGame = false;

	FEditorDelegates::BeginPIE.AddRaw(this, &FSharpUnrealEditorModule::OnBeginPIE);
	FEditorDelegates::EndPIE.AddRaw(this, &FSharpUnrealEditorModule::OnEndPIE);
}

void FSharpUnrealEditorModule::ShutdownModule()
{
	GLog->Logf(ELogVerbosity::Log, TEXT("[SharpUnrealEditor] ShutdownModule."));
	auto& PropertyModule =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(FName("MonoComponent"));
	PropertyModule.NotifyCustomizationModuleChanged();

	auto& DirWatcherModule =
		FModuleManager::LoadModuleChecked<FDirectoryWatcherModule>("DirectoryWatcher");
	auto DirWatcher = DirWatcherModule.Get();

	if (DirWatcher)
	{		
		FString runtime = FPaths::Combine(FPaths::GameDir(), TEXT("RuntimeLibs"));
		DirWatcher->UnregisterDirectoryChangedCallback_Handle(
			runtime, OnBinaryDirChangedDelegateHandle
		);
	}
	else {
		GLog->Logf(TEXT("[SharpUnrealEditor] DirWatcher is null."));
	}
}

void FSharpUnrealEditorModule::OnBeginPIE(const bool bIsSimulating) 
{
	IsEditorRunningGame = true;
}

void FSharpUnrealEditorModule::OnEndPIE(const bool bIsSimulating) 
{
	IsEditorRunningGame = false;
}

void FSharpUnrealEditorModule::OnBinaryDirChanged(const TArray<FFileChangeData>& FileChanges)
{
	for (auto& FileChange : FileChanges)
	{
		bool bActionRelevant = (FileChange.Action == FFileChangeData::FCA_Added)
			|| (FileChange.Action == FFileChangeData::FCA_Modified);

		const FString& Filename = FileChange.Filename;
		
		if (bActionRelevant && Filename.EndsWith(TEXT(".dll")) &&
			(FPaths::GetBaseFilename(Filename) == TEXT("MainAssembly")))
		{
			auto time = IFileManager::Get().GetTimeStamp(*MainAssemblyPath);
			auto delta = time - LastAssemblyMotifyTimeStamp;
			LastAssemblyMotifyTimeStamp = time;
			//如果代码更新了而且编辑器没有再运行的话
			if (delta.GetSeconds() > 1 && !IsEditorRunningGame)
			{				
				GLog->Logf(TEXT("[SharpUnrealEditor] FileChanged %s , %d"), *Filename, (int32)FileChange.Action);
				//在这里可以进行Mono的dll重新加载了
			}
			break;
		}
		
	}
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSharpUnrealEditorModule, SharpUnrealEditor)