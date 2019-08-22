class HordeLoadouts
{
	private ref array<ref HordeLoadout> m_Loadouts;
	
	const string JSONPATH = "$profile:InfectedHorde/Loadouts/Loadouts.Json";

   void HordeLoadouts()
   {
		if(GetGame().IsClient() || !GetGame().IsMultiplayer()) return;
		
		m_Loadouts = new array<ref HordeLoadout>;
		MakeDirectory("$profile:InfectedHorde/Loadouts/");
		
		if(!FileExist(JSONPATH))
		{
			AddInfectedLoadout(HordeCategory.Civilian, "ZmbF_CitizenANormal_Blue", {"beaniehat_blue", "mountainbag_blue", "PressVest_Blue"}, {"m4a1", "Mag_STANAG_30Rnd", "AmmoBox_556x45_20Rnd"});
			AddInfectedLoadout(HordeCategory.Civilian, "ZmbM_CitizenASkinny_Grey", {"BeanieHat_Grey", "mountainbag_Grey", "UKAssVest_Black"}, {"CombatKnife", "TacticalBaconCan", "Matchbox", "WaterBottle"});
			AddInfectedLoadout(HordeCategory.Civilian, "ZmbM_CitizenBFat_Red", {"BeanieHat_Red", "MountainBag_Red", "UKAssVest_Black"}, {"Rag", "Epinephrine", "Canteen"});
			AddInfectedLoadout(HordeCategory.Civilian, "ZmbM_CitizenBFat_Green", {"BeanieHat_Green", "MountainBag_Green", "UKAssVest_Black"}, {"rice", "rice", "rice", "rice", "rice"});
			
			AddInfectedLoadout(HordeCategory.Military, "ZmbM_usSoldier_normal_Woodland", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.Military, "ZmbM_usSoldier_normal_Desert", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.Military, "ZmbM_Soldier", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.Military, "ZmbM_SoldierAlice", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.FirstResponder, "ZmbF_NurseFat", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.FirstResponder, "ZmbM_DoctorFat", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			AddInfectedLoadout(HordeCategory.FirstResponder, "ZmbM_FirefighterNormal", {"beaniehat_blue", "mountainbag_green", "ukassvest_khaki"}, {"rice", "rice", "rice", "rice", "rice"});
			Save();
			return;
		}
		
		Load();
   }
	
	void Save()
   {
		JsonFileLoader<HordeLoadouts>.JsonSaveFile(JSONPATH, this);
   }

   void Load()
   {
		JsonFileLoader<HordeLoadouts>.JsonLoadFile(JSONPATH, this);
   }
	
	private void AddInfectedLoadout(HordeCategory category, string name, array<string> attachments, array<string> loot)
	{
		m_Loadouts.Insert(new HordeLoadout(category, name, attachments, loot));
	}
	
	HordeLoadout GetRandomLoadout(HordeCategory category)
	{
		if(category == HordeCategory.None)
			return m_Loadouts.GetRandomElement();
		
		if(category != HordeCategory.None)
		{
			autoptr HordeLoadout loadout = m_Loadouts.GetRandomElement();
			
			while(loadout.GetCategory() != category)
			{
				loadout = m_Loadouts.GetRandomElement();
			}
			return loadout;
		}
		
		return null;
	}
	
}