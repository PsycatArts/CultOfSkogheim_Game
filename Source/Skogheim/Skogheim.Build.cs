// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Skogheim : ModuleRules
{
	public Skogheim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Slate", "SlateCore", "HTTP", "Json", "JsonUtilities" });
	}
}
