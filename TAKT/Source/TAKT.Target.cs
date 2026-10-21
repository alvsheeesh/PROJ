using UnrealBuildTool;
using System.Collections.Generic;

public class TAKTTarget : TargetRules
{
	public TAKTTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("TAKT");
	}
}
