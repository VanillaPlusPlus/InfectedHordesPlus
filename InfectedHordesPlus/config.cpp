class config
{
   class InfectedHordePlus
   {
      units[] = {};
      weapons[] = {};
      requiredVersion = 0.1;
      requiredAddons[] =
      {
         "DZ_Data"
      };
   };
};

class CfgMods
{
   class InfectedHordePlus
   {
      dir = "InfectedHordePlus";
      picture = "";
      action = "";
      hideName = 1;
      hidePicture = 1;
      name = "InfectedHordePlus";
      credits = "GravityWolf & DaOne";
      author = "GravityWolf & DaOne";
      authorID = "0";
      version = "0.1";
      extra = 0;
      type = "mod";
      dependencies[] =
      {
         "World"
      };

      class defs
      {
         class worldScriptModule
         {
            value = "";
            files[] =
            {
               "InfectedHordePlus/4_World"
            };
         };
      };
   };
};