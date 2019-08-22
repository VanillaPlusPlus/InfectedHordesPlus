modded class PluginManager
{

   override void Init()
   {
      super.Init();

      RegisterPlugin("HordeManager", false, true);
   }
}