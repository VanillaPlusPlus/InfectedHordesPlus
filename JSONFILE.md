This file provide as much information about the JSON config as possible.

### ** HordeConfig.json **

```
    m_ActiveHordeMax : The max amount of hordes on the map,
    m_SpawnTime : How long till the system looks to spawn another horde. 
    m_DespawnTime : How long till the system checks for despawn. 0 will result in 30 seconds despawn time,

    m_MinInfectedCount : Minimum amount of infected in a horde,
    m_MaxInfectedCount Maximum amount of infected in a horde,
    m_CanDeleteHordeOnDespawn: Will delete the infected from the horde on despawn,
    m_DeleteOnlyAlive: Will only delete infected that are alive on despawn,
    m_CanReleaseHordeLocations: Releasing the horde location allowing it to reused/have a horde spawned there again. This allows you only use each array once.

    m_CanSendSpawnMessage: Allows spawn message to happen,
    m_CanSendDespawnMessage: Allows despawn message to happen,
    m_CanSendSpawnLocation: Will show spawn location,
    m_CanPrintToLogs: Allows printing to log files for debugging.

    m_HordeSpawnLocations: Array of horde locations,
        m_Name: Name of location,
        m_Category: Horde Category ( 0, 1, 2 are specific groups you may set hordes to be, or you can use 3 to only allow random from all infected),
        m_SpawnOffset: How random variation to each infected's spawn position higher the number the further apart they can spawn,
        m_Position: Location of the area
```

### ** Loadouts.Json **
```
	m_Loadouts : The collection of loadouts the system has to choose from,
		m_Name : Name of the zombie to spawn
            m_Category : The category which the zombie can be spawned in,
            m_Gear : List of item names that will be attached to the zombie,
            m_Loot : List of item names that will be put into the zombies inventory
```

** Note: **
If you forget a comma before you next position it will not work because of a incorrect syntax. If you add a comma after your last position, you also will throw an error. If you are just simply not good with json formatting [Go here](httpsjsoneditoronline.org).