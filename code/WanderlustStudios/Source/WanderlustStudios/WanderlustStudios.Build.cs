// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WanderlustStudios : ModuleRules
{
	public WanderlustStudios(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"AutomationTest"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"WanderlustStudios",
			"WanderlustStudios/Variant_Horror",
			"WanderlustStudios/Variant_Horror/UI",
			"WanderlustStudios/Variant_Shooter",
			"WanderlustStudios/Variant_Shooter/AI",
			"WanderlustStudios/Variant_Shooter/UI",
			"WanderlustStudios/Variant_Shooter/Weapons",
			"WanderlustStudios/Tests"
		});
		 
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
