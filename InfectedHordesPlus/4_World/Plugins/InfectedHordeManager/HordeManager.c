class HordeManager : PluginBase
{
    private ref Timer m_Timer;
	private ref Timer m_DespawnTimer;
	
	private bool hasInit = false;
	
    private ref HordeConfig m_Config;
    private ref HordeLoadouts m_HordeLoadouts;
	private ref array<ref InfectedHorde> m_Hordes;

   void HordeManager()
   {
      if(GetGame().IsClient() || !GetGame().IsMultiplayer()) return;
      MakeDirectory("$profile:InfectedHorde");
		
      m_Timer = new Timer(CALL_CATEGORY_GAMEPLAY);
		m_DespawnTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
		
      m_Config = new HordeConfig();
      m_HordeLoadouts = new HordeLoadouts();
		
		m_Hordes = new array<ref InfectedHorde>;
   }

   void ~HordeManager()
   {
      delete m_Timer;
      delete m_DespawnTimer;
      delete m_Config;
	  delete m_HordeLoadouts;
	  delete m_Hordes;
   }

   override void OnInit()
   {
		m_Timer.Run(m_Config.GetSpawnTimeLength(), this, "AddHorde", null, true);
		hasInit = true;
   }
	
	override void OnUpdate(float delta_time)
	{
		if(!hasInit) return;
		
		
		if(m_Config.GetMaxHordes() == m_Hordes.Count())
		{
			if(!m_Timer.IsRunning()) return;
			
			if(m_Config.CanPrintToLogs())
				Print("[HordeManager]:: OnUpdate: Stopping Spawn Timer");
			
			m_Timer.Stop();
		}
		
		if(m_Hordes.Count() == 0)
		{
			if(!m_DespawnTimer.IsRunning()) return;
			
			if(m_Config.CanPrintToLogs())
				Print("[HordeManager]:: OnUpdate: Stopping Despawn Timer");
			
			m_DespawnTimer.Stop();
		}
		
		if(m_Hordes.Count() > 0)
		{
			if(!m_DespawnTimer.IsRunning())
			{
				if(m_Config.CanPrintToLogs())
					Print("[HordeManager]:: OnUpdate: Starting Despawn Timer");
				
				int time = 30;
				if(m_Config.GetDespawnTimeLength() != 0)
					time = m_Config.GetDespawnTimeLength();
				
				m_DespawnTimer.Run(time, this, "RemoveHorde", null, true);			
			}
		}
		
		if(m_Hordes.Count() != m_Config.GetMaxHordes())
		{
			if(!m_Timer.IsRunning())
			{
				if(m_Config.CanPrintToLogs())	
					Print("[HordeManager]:: OnUpdate: Starting Spawn Timer");
				
		     	m_Timer.Run(m_Config.GetSpawnTimeLength(), this, "AddHorde", null, true);			
			}
		}
	}

   override void OnDestroy()
   {
      delete this;
   }
	
	void RemoveHorde()
	{
		Print("Count: " + m_Hordes.Count());
		if(m_Hordes.Count() == 0) return;
		
		if(m_Config.GetDespawnTimeLength() == 0)
		{
			array<string> names = new array<string>;
			foreach(ref InfectedHorde horde : m_Hordes)
			{
				ref InfectedHorde hordeToBeRemoved = horde;
				
				if(hordeToBeRemoved == null)
				{
					Print("[HordeManager]:: RemoveHorde(): Removing Null horde.");
					m_Hordes.RemoveItem(horde);
					continue;
				}				
				
				string name = m_Config.GetNameByVector(hordeToBeRemoved.GetPosition());

				if(hordeToBeRemoved.CanRelease())
				{
					names.Insert(name);
					
					if(m_Config.CanReleaseHorde())
						m_Config.ReleaseLocation(hordeToBeRemoved.GetPosition());

					m_Hordes.RemoveItem(hordeToBeRemoved);								 
					delete hordeToBeRemoved;
				}
			}
			
			if(names.Count() > 0 && names.Count() < 2)
				SendDespawnMessage(names[0]);
			
			if(names.Count() > 1)
				SendDespawnMessage("Multiple Locations");
			
			return;
		}
		
		vector oldPos = m_Hordes[0].GetPosition();
		string spawnName = m_Config.GetNameByVector(oldPos);

		if(m_Config.CanPrintToLogs())
			Print("[HordeManager]:: RemoveHorde: Removing horde from: " + spawnName);
				
		if(m_Config.CanReleaseHorde())
			m_Config.ReleaseLocation(oldPos);
		
		ref InfectedHorde removedHorde = m_Hordes[0];
		
		m_Hordes.RemoveItem(removedHorde);
		
		if(m_Config.CanDeleteHorde())
			delete removedHorde;
						
		Print("Count: " + m_Hordes.Count());
	}
	
   void AddHorde()
   {
		if(m_Config.CanPrintToLogs())
      	Print("[HordeManager]:: AddHorde: Added Horde");
		
		if(m_Hordes.Count() == m_Config.GetMaxHordes()) return;
				
		int hordeSize = m_Config.GetHordeCount();
		ref HordeSpawnLocation location = m_Config.GetRandomSpawn();
		
		if(location == null)
		{
			if(m_Config.CanPrintToLogs())
				Print("[HordeManager:: AddHorde: Couldn't find free spawn.");
			
			return;
		}
		
		vector hordePosition = location.GetPosition();
		
		if(hordePosition == "0 0 0")
		{
			if(m_Config.CanPrintToLogs())
				Print("[HordeManager:: AddHorde: Couldn't find free spawn.");
			
			return;
		}
		
		ref InfectedHorde newHorde = new InfectedHorde(hordePosition, m_Config.CanDeleteHorde(), m_Config.DeleteOnlyAlive());
		m_Hordes.Insert(newHorde);
		
		autoptr array<string> gear = new array<string>;
		autoptr array<string> loot = new array<string>;
		HordeLoadout selectedLoadout;
		EntityAI infected;
		
		if(m_Config.CanPrintToLogs())	
			Print("[HordeManager:: AddHorde: Horde Spawned at: " + hordePosition.ToString(false) + " : " + location.GetName());
		
		SendSpawnMessage(location.GetName());

		for(int i = 0; i < hordeSize; i++)
		{
			selectedLoadout = m_HordeLoadouts.GetRandomLoadout(location.GetCategory());
			
			if(selectedLoadout == null)
			{
				if(m_Config.CanPrintToLogs())
					Print("[HordeManager]:: AddHorde: Using random loadout");
				
				selectedLoadout = m_HordeLoadouts.GetRandomLoadout(HordeCategory.None);
			}
			
			selectedLoadout.GetGear(gear);
			selectedLoadout.GetLoot(loot);
			
			location.GetOffsetVector(hordePosition);
			infected = EntityAI.Cast(GetGame().CreateObject(selectedLoadout.GetName(), hordePosition, false, true));
			
			if(infected == null)
			{
				Print("[HordeManager]:: AddHorde: Infected Name: " + selectedLoadout.GetName() + " is not a spawnable game object.");
				Print("[HordeManager]:: AddHorde: Choosing a another loadout.");
				selectedLoadout = m_HordeLoadouts.GetRandomLoadout(location.GetCategory());
				selectedLoadout.GetGear(gear);
				selectedLoadout.GetLoot(loot);
			}else
			{
				foreach(string str : gear)
				{
					infected.GetInventory().CreateAttachment(str);
				}
				
				foreach(string item : loot)
				{
					infected.GetInventory().CreateInInventory(item);
				}

				infected.PlaceOnSurface();
				newHorde.AddInfected(infected);
			}
		}
   }
	void SendSpawnMessage(string name)
	{
		if(m_Config.CanSendSpawnMessage())
		{
			string msg = "A Horde has been spotted";
			
			if(m_Config.CanSendSpawnLocation())
			{
				msg = msg + " at " + name;
			}
			
			NotificationSystem.SendNotificationToPlayerIdentityExtended(null, 5, "Infected Horde", msg, "set:ccgui_enforce image:Icon40Emergency");
		}
	}
	void SendDespawnMessage(string name)
	{	
		if(m_Config.CanSendDespawnMessage())
		{
			string despawnMessage = "A Horde was removed";
			if(m_Config.CanSendSpawnMessage())
			{
				despawnMessage = despawnMessage + " at " + name;
			}
			NotificationSystem.SendNotificationToPlayerIdentityExtended(null, 5, "Infected Horde", despawnMessage, "set:ccgui_enforce image:Icon40Emergency");
		}
	}
}