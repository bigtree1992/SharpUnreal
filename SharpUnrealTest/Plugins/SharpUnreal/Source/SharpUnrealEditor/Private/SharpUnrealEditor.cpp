// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SharpUnrealEditorPrivatePCH.h"
#include "IDirectoryWatcher.h"
#include "DirectoryWatcherModule.h"
#include "Settings/ProjectPackagingSettings.h"

#include "MonoComponentDetails.h"
#include "SharpUnreal.h"
#include "Editor.h"
#include "MonoRuntime.h"

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
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (DirWatcher)
	{
		FString build = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("BuildLibs"));
		GLog->Logf(TEXT("[SharpUnrealEditor] BuildLibs Path %s"), *build);

		MainAssemblyPath = build / TEXT("MainAssembly.dll");

		DirWatcher->RegisterDirectoryChangedCallback_Handle(
			build, IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FSharpUnrealEditorModule::OnRuntimeDllChanged),
			OnDllChangedHandle);

		FString Saved = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("Saved") ); // TEXT("StagedBuilds")
		if (!PlatformFile.DirectoryExists(*Saved)) 
		{
			PlatformFile.CreateDirectory(*Saved);
		}

		FString StageBuilds = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("Saved")/ TEXT("StagedBuilds"));
		if (!PlatformFile.DirectoryExists(*StageBuilds))
		{
			PlatformFile.CreateDirectory(*StageBuilds);
		}

		DirWatcher->RegisterDirectoryChangedCallback_Handle(
			StageBuilds, IDirectoryWatcher::FDirectoryChanged::CreateRaw(this, &FSharpUnrealEditorModule::OnStageBuildsChanged),
			OnStageBuildsHandle);
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
		FString build = FPaths::Combine(FPaths::GameDir(), TEXT("BuildLibs"));
		DirWatcher->UnregisterDirectoryChangedCallback_Handle(build, OnDllChangedHandle);

		FString StageBuilds = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("Saved") / TEXT("StagedBuilds"));
		DirWatcher->UnregisterDirectoryChangedCallback_Handle(StageBuilds, OnStageBuildsHandle);
	}
	else {
		GLog->Logf(TEXT("[SharpUnrealEditor] DirWatcher is null."));
	}
}

void FSharpUnrealEditorModule::OnBeginPIE(const bool bIsSimulating) 
{
	IsEditorRunningGame = true;

	MonoRuntime::Instance()->OnBeginPIE(bIsSimulating);
}

void FSharpUnrealEditorModule::OnEndPIE(const bool bIsSimulating) 
{
	IsEditorRunningGame = false;
	MonoRuntime::Instance()->OnEndPIE(bIsSimulating);
}

void FSharpUnrealEditorModule::OnRuntimeDllChanged(const TArray<FFileChangeData>& FileChanges)
{
	for (auto& FileChange : FileChanges)
	{
		bool bActionRelevant = (FileChange.Action == FFileChangeData::FCA_Added)
			|| (FileChange.Action == FFileChangeData::FCA_Modified);

		const FString& Filename = FileChange.Filename;
		
		if (bActionRelevant && Filename.EndsWith(TEXT(".dll")) &&
			(FPaths::GetBaseFilename(Filename) == TEXT("MainAssembly") || FPaths::GetBaseFilename(Filename) == TEXT("UnrealEngine")))
		{
			auto time = IFileManager::Get().GetTimeStamp(*MainAssemblyPath);
			auto delta = time - LastAssemblyMotifyTimeStamp;
			LastAssemblyMotifyTimeStamp = time;
			//如果代码更新了而且编辑器没有再运行的话
			if (delta.GetSeconds() > 1 && !IsEditorRunningGame)
			{				
				//GLog->Logf(TEXT("[SharpUnrealEditor] FileChanged %s , %d"), *Filename;
				//在这里可以进行Mono的dll重新加载了
				auto& SharpUnreal =
					FModuleManager::LoadModuleChecked<FSharpUnrealModule>("SharpUnreal");
				
				SharpUnreal.ReloadMainAssembly();
			}
			break;
		}
		
	}
}

void FSharpUnrealEditorModule::OnStageBuildsChanged(const TArray<FFileChangeData>& InFileChanges) 
{
	auto* PackagingSettings =
	Cast<UProjectPackagingSettings>(UProjectPackagingSettings::StaticClass()->GetDefaultObject());
	if (!PackagingSettings)
	{
		return;
	}

	FString& Staging = PackagingSettings->StagingDirectory.Path;

	if (Staging.Len() == 0)
	{
		return;
	}

	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	for (auto& FileChange : InFileChanges)
	{
		if (FileChange.Action != FFileChangeData::FCA_Modified)
		{
			continue;
		}

		const FString path =
			FPaths::ConvertRelativePathToFull(FileChange.Filename);

		if (!path.EndsWith(TEXT("Binaries/Win64")))
		{
			continue;
		}

		int32 index = path.Find(TEXT("WindowsNoEditor"));
		if (index == -1)
		{
			continue;
		}

		FString Target = FPaths::ConvertRelativePathToFull(Staging);
		if (!PlatformFile.DirectoryExists(*Target))
		{
			return;
		}

		FString TargetWindowNoEditor = Target / TEXT("WindowsNoEditor");
		if (!PlatformFile.DirectoryExists(*TargetWindowNoEditor))
		{
			PlatformFile.CreateDirectory(*TargetWindowNoEditor);
		}

		FString Game = path.Right(path.Len() - index - 16);
		Game.RemoveFromEnd(TEXT("/Binaries/Win64"));
		
		FString TargetGame = TargetWindowNoEditor / Game;
		if (!PlatformFile.DirectoryExists(*TargetGame))
		{
			PlatformFile.CreateDirectory(*TargetGame);
		}
		FString TargetBinaries = TargetGame / TEXT("Binaries");
		if (!PlatformFile.DirectoryExists(*TargetBinaries))
		{
			PlatformFile.CreateDirectory(*TargetBinaries);
		}
		FString TargetWin64 = TargetBinaries / TEXT("Win64");
		if (!PlatformFile.DirectoryExists(*TargetWin64))
		{
			PlatformFile.CreateDirectory(*TargetWin64);
		}

		FString TargetDll = TargetWin64 / TEXT("mono-2.0-sgen.dll");
		FString SourceBin = FPaths::ConvertRelativePathToFull(
			FPaths::GameDir() / TEXT("Binaries") / TEXT("Win64") / TEXT("mono-2.0-sgen.dll"));
		if (PlatformFile.FileExists(*SourceBin) && !PlatformFile.FileExists(*TargetDll))
		{
			PlatformFile.CopyFile(*TargetDll, *SourceBin);
		}

		FString TargetDlls = TargetGame / TEXT("RuntimeLibs");
		FString SourceDlls = FPaths::ConvertRelativePathToFull(FPaths::GameDir() / TEXT("RuntimeLibs"));
		if (PlatformFile.DirectoryExists(*TargetDlls))
		{
			if (!PlatformFile.DeleteDirectoryRecursively(*TargetDlls))
			{
				GLog->Logf(ELogVerbosity::Error, TEXT("[PostBuild] Delete %s Directory Failed."), *TargetDlls);
			}
		}

		if (!PlatformFile.CopyDirectoryTree(*TargetDlls, *SourceDlls,true))
		{
			GLog->Logf(ELogVerbosity::Error, TEXT("[PostBuild] CopyDirectoryTree Failed : %s -> %s"), *SourceDlls, *TargetDlls);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSharpUnrealEditorModule, SharpUnrealEditor)