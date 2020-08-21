enum HordeCategory
{
	Military,
	FirstResponder,
	Civilian,
	None
}

class HordeMessageSettings
{
	private bool m_CanSendSpawnMessage;
	private bool m_CanSendDespawnMessage;
	private bool m_CanSendSpawnLocation;
	private bool m_CanPrintToLogs;

	void HordeMessageSettings()
	{
		m_CanSendSpawnLocation = 1;
		m_CanSendSpawnMessage = 1;
		m_CanSendDespawnMessage = 1;
		m_CanPrintToLogs = 1;
	}
	
	bool CanSendDespawnMessage()
	{
		return m_CanSendSpawnMessage;
	}
	bool CanSendSpawnMessage()
	{
		return m_CanSendDespawnMessage;
	}
	bool CanSendLocation()
	{
		return m_CanSendSpawnLocation;
	}
	
	bool CanPrintToLogs()
	{
		return m_CanPrintToLogs;
	}
}

class HordeSettings
{
   private int m_SpawnTime;
	private int m_DespawnTime;
   private int m_MinInfectedCount;
   private int m_MaxInfectedCount;
	
	private bool m_CanDeleteHordeOnDespawn;
	private bool m_DeleteOnlyAlive;
	private bool m_CanReleaseHordeLocations;

	void HordeSettings()
	{
		m_SpawnTime = 300;
		m_DespawnTime = 600;
		m_MinInfectedCount = 1;
		m_MaxInfectedCount = 10;
		m_CanDeleteHordeOnDespawn = 1;
		m_DeleteOnlyAlive = 1;
		m_CanReleaseHordeLocations = 1;
	}
		
	int GetSpawnTime()
	{
		return m_SpawnTime;
	}
	
	int GetDespawnTime()
	{
		return m_DespawnTime;
	}
	
	int GetMinCount()
	{
		return m_MinInfectedCount;
	}
	
	int GetMaxCount()
	{
		return m_MaxInfectedCount;
	}
	
	bool CanDeleteHordeOnDespawn()
	{
		return m_CanDeleteHordeOnDespawn;	
	}
	
	bool CanOnlyDeleteAlive()
	{
		return m_DeleteOnlyAlive;
	}
	
	bool CanReleaseHorde()
	{
		return m_CanReleaseHordeLocations;
	}
}

class HordeConfig
{
   [NonSerialized()]
   const string JSONPATH = "$profile:InfectedHorde/Config/HordeConfig.json";

	private int m_ActiveHordeMax;
	private ref HordeSettings m_HordeSettings;
	private ref HordeMessageSettings m_NotificationSettings;
   private ref array<ref HordeSpawnLocation> m_HordeSpawnLocations;

   void HordeConfig()
   {
      if(GetGame().IsClient() || !GetGame().IsMultiplayer()) return;

      MakeDirectory("$profile:InfectedHorde/Config");
      m_HordeSpawnLocations = new array<ref HordeSpawnLocation>;
		m_HordeSettings = new HordeSettings();
		m_NotificationSettings = new HordeMessageSettings();
		

      if(!FileExist(JSONPATH))
      {
			Print("[HordeConfig]:: HordeConfig: Creating Default File");

			m_ActiveHordeMax = 3;
			
			InitSpawnLocations();
         Save();
         return;
      }
		Print("[HordeConfig]:: HordeConfig: Loading File");
      Load();
   }

   void Load()
   {
      JsonFileLoader<HordeConfig>.JsonLoadFile(JSONPATH, this);
   }

   void Save()
   {
      JsonFileLoader<HordeConfig>.JsonSaveFile(JSONPATH, this);
   }
	
	string GetNameByVector(vector v)
	{
		foreach(HordeSpawnLocation location : m_HordeSpawnLocations)
		{
			if(location.GetPosition() == v)
			{
				return location.GetName();
			}
		}
		
		return "0 0 0";
	}

	void InitSpawnLocations()
	{
		AddHordeSpawnLocation(HordeCategory.Military, "WhereTheFuckIAm", "8500 0 8500", 10);
		AddHordeSpawnLocation(HordeCategory.FirstResponder, "MiddleOfFuckingMap", "3500 0 3500", 10);
		AddHordeSpawnLocation(HordeCategory.Civilian, "MiddleOfFuckingMap", "7500 0 7500", 10);
		AddHordeSpawnLocation(HordeCategory.None, "WhereTheFuckIAm", "10000 0 10000", 10);
		
	}
	
   void AddHordeSpawnLocation(HordeCategory category, string name, vector position, int radius)
   {
      m_HordeSpawnLocations.Insert(new HordeSpawnLocation(category, name, position, radius));
   }
	
	HordeSpawnLocation GetRandomSpawn()
	{
		ref HordeSpawnLocation temp = m_HordeSpawnLocations.GetRandomElement();
		int count = 0;
				
		while(count < m_HordeSpawnLocations.Count() * 2 && temp.IsAlive())
		{
			temp = m_HordeSpawnLocations.GetRandomElement();
			
			if(!temp.IsAlive())
				break;
			
			count++;
		}
      
		if(!temp.IsAlive())
		{
			temp.SetAlive();
			return temp;
		}
		
		return null;
	}
	
	void ReleaseLocation(vector v)
	{
		foreach(HordeSpawnLocation location : m_HordeSpawnLocations)
		{
			if(v == location.GetPosition())
			{
				if(location.IsAlive())
				{
					location.SetAlive();
					break;
				}
			}
		}
	}
	
	bool CanSendDespawnMessage()
	{
		return m_NotificationSettings.CanSendDespawnMessage();
	}
	
	bool CanSendSpawnMessage()
	{
		return m_NotificationSettings.CanSendSpawnMessage();
	}
	
	bool CanSendSpawnLocation()
	{
		return m_NotificationSettings.CanSendLocation();
	}
	
	bool CanDeleteHorde()
	{
		return m_HordeSettings.CanDeleteHordeOnDespawn();
	}
	
	bool DeleteOnlyAlive()
	{
		return m_HordeSettings.CanOnlyDeleteAlive();
	}
	
	bool CanReleaseHorde()
	{
		return m_HordeSettings.CanReleaseHorde();
	}
	
	bool CanPrintToLogs()
	{
		return m_NotificationSettings.CanPrintToLogs();
	}
	
	int GetDespawnTimeLength()
	{
		return m_HordeSettings.GetDespawnTime();
	}
	
   int GetSpawnTimeLength()
   {
      return m_HordeSettings.GetSpawnTime();
   }
	
	int GetHordeCount()
	{
		return Math.RandomIntInclusive(m_HordeSettings.GetMinCount(), m_HordeSettings.GetMaxCount());
	}
	
	int GetMaxHordes()
	{
		return m_ActiveHordeMax;
	}
}