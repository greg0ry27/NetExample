// Fill out your copyright notice in the Description page of Project Settings.
using System.IO;
using UnrealBuildTool;

public class NetExample : ModuleRules
{
	public NetExample(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Networking", "Sockets" });        
            
        string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/"));
        string LibrariesPath = Path.Combine(ThirdPartyPath, "lib");
        string IncludesPath = Path.Combine(ThirdPartyPath, "include");

        PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libprotobuf.lib"));
        PublicIncludePaths.Add(IncludesPath);
        //Definitions.Add("BOOST_SYSTEM_NOEXCEPT");
    }
}
