// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameJam : ModuleRules
{
	public GameJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
		
		PublicIncludePaths.AddRange(new string[]
		{
			"GameJam/Public/Player",
			"GameJam/Public/PlayerObjects",
			"GameJam/Public/Components",
			"GameJam/Public/Pickable",
			"GameJam/Public/UI",
			"GameJam/Public/Menu/UI",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}