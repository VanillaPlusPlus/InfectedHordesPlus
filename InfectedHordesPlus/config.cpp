class CfgMods
{
	class InfectedHordesPlus
	{
		dir="InfectedHordesPlus";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Vanilla++ Survival";
		credits="GravityWolf";
		author="GravityWolf";
		authorID="420420";
		version="Version 1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"InfectedHordesPlus/4_World"
				};
			};
		};
	};
};
class CfgPatches
{
	class VPP_InfectedHordesPlus
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};