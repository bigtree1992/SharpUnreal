// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System;
using System.IO;


public class SharpUnreal : ModuleRules
{
	private string ThirdPartPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdPart")); }
    }

    private void BuildWithMono(TargetInfo Target)
    {
        switch (Target.Platform)
        {
            case UnrealTargetPlatform.Win64:
                PublicIncludePaths.Add(
                    Path.Combine(ThirdPartPath, "Mono", "include"));
                PublicAdditionalLibraries.Add(
                    Path.Combine(ThirdPartPath, "Mono", "lib", "Win64", "mono-2.0-sgen.lib"));
                break;
            case UnrealTargetPlatform.Win32:
            case UnrealTargetPlatform.Mac:
            case UnrealTargetPlatform.Android:
            case UnrealTargetPlatform.IOS:
            default:
                throw new BuildException("SharpUnreal current not supported on platform '{0}'", Target.Platform.ToString());
        }
    }

	public SharpUnreal(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"SharpUnreal/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"SharpUnreal/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "LevelSequence",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
        BuildWithMono(Target);
    }
}
