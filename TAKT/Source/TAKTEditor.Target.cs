using UnrealBuildTool;
using System.Collections.Generic;

public class TAKTEditorTarget : TargetRules
{
	public TAKTEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("TAKT");
	}
}
