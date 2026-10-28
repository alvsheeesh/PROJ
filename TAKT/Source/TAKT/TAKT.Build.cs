using UnrealBuildTool;

public class TAKT : ModuleRules
{
	public TAKT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// El código se organiza en subcarpetas por dominio (Line/, ...).
		// Con la raíz del módulo en la ruta de includes se escribe
		// #include "Line/ConveyorBelt.h" desde cualquier fichero.
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"PhysicsCore"
		});
	}
}
