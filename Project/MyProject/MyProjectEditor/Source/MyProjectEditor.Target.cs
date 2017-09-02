// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

/**
 * @reference https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */
// ���������� MyProjectEditor �� sln ���ǲ��ᱻ����ģ�ֻ������ Editor ��ʱ�򣬲Ż���� MyProjectEditor ģ�飬���û�вŻ����±��룬���� OutExtraModuleNames.Add("MyProjectEditor"); ǿ�Ʊ���
public class MyProjectEditorTarget : TargetRules
{
    //public MyProjectEditorTarget(TargetInfo Target)
    public MyProjectEditorTarget(TargetInfo Target) : base(Target)
    {
		this.Type = TargetType.Editor;

        // UnrealEngine\Engine\Source\Programs\UnrealBuildTool\System\RulesCompiler.cs
        // public bool bBuildAllPlugins = false;

        // UnrealEngine\Engine\Source\Programs\UnrealBuildTool\Configuration\UEBuildTarget.cs
        // Set the list of plugins that should be built
        //if (Rules.bBuildAllPlugins)
        //{
        //    BuildPlugins = new List<PluginInfo>(ValidPlugins);
        //}
        //else
        //{
        //    BuildPlugins = new List<PluginInfo>(EnabledPlugins);
        //}

        // UnrealEngine\Engine\Source\UE4Editor.Target.cs
        // ���������ú�MyProject\Plugins\MyPlugin �Ż����
        this.bBuildAllPlugins = true;

        // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
        this.ExtraModuleNames.Add("MyProject");
        //ExtraModuleNames.Add("MyProjectEditor");
        //OutExtraModuleNames.Add("MyProjectEditor");
    }

    //
    // TargetRules interface.
    //

    // Engine\Source\Programs\UnrealBuildTool\System\RulesCompiler.cs
    // <param name="OutExtraModuleNames">Output list of extra modules that this target could utilize</param>
    // warning : SetupBinaries() is deprecated in the 4.16 release. From the constructor in your .target.cs file, use ExtraModuleNames.Add("Foo") to add modules to your target, or set LaunchModuleName = "Foo" to override the name of the launch module for program targets.
 //   public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
 //       // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 //       // ����ֶξ����Ƿ���뵱ǰ���̣�֮ǰд�� "MyProject" ����� "MyProjectEditor" û�б���
 //       OutExtraModuleNames.Add("MyProject");
 //       //OutExtraModuleNames.Add("MyProjectEditor");
 //   }

    public override void SetupGlobalEnvironment(
        TargetInfo Target,
        ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
        ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
        )
    {
        UEBuildConfiguration.bBuildEditor = true;   // �����Ƿ�༭ MyProjectEditor�����Ǽ�ʹ��ʼ������������ļ� MyProject\Source\MyProjectEditor.Target.cs �е� OutExtraModuleNames.Add("MyProjectEditor"); Ҳ������� MyProjectEditor

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            //WindowsPlatform.bUseVCCompilerArgs = true;
        }
    }
}