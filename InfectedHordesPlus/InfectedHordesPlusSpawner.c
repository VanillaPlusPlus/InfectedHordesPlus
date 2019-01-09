/*
   _____                                      
  / ____|                                     
 | (___  _ __   __ ___      ___ __   ___ _ __ 
  \___ \| '_ \ / _` \ \ /\ / / '_ \ / _ \ '__|
  ____) | |_) | (_| |\ V  V /| | | |  __/ |   
 |_____/| .__/ \__,_| \_/\_/ |_| |_|\___|_|   
        | |                                   
        |_|                                   
*/

#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\ServerAddons\\InfectedHordesPlus\\InfectedHordesPlus.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\ServerAddons\\InfectedHordesPlus\\InfectedHordesPlusConfig.c"


class InfectedHordesPlusSpawner
{
	private float timeSnapshot;
	private float lifeTimeClock;

	ref array<ref InfectedHordesPlus> m_hordes;

	ref InfectedHordesPlusConfig config;


	void InfectedHordesPlusSpawner()
	{
		 config = new InfectedHordesPlusConfig();
         config.load();
		 m_hordes = new array<ref InfectedHordesPlus>;
	}

    void Init(){
		Print("Infected Hordes...INIT!");
    }

    void onUpdate(float timeslice){
    	timeSnapshot += timeslice;
    	lifeTimeClock += timeslice;

    	if(config.getHordeSpawnTime() <= timeSnapshot){
    		timeSnapshot = 0;

    		if(m_hordes.Count() != config.getMaxHordes()){
    			ref InfectedHordesPlus insertHorde = new InfectedHordesPlus(config.getHordeZoneLocation(), config.getMinInfectedCount(), config.getMaxInfectedCount(), config.getZombieClasses(), config.getLootChoices(), config.getWeaponLootChoices());
    			m_hordes.Insert(insertHorde);
    			Print("Horde has been sighted at " + insertHorde.getLocation().ToString());
    		}
    	}

        if(m_hordes.Count() == 0){
            lifeTimeClock = 0;
            return;
        }

    	if(m_hordes.Count() != 0){
			foreach(InfectedHordesPlus horde : m_hordes){
				horde.addLifeTime(timeslice);

				if(horde.hasLivedLife(config.getDespawnTime())){
					Print("Horde spawned at " + horde.getLocation().ToString() + " has lived it's life and depsawned.");
					horde.deleteHorde();
					m_hordes.RemoveItem(horde);
				}
			}
    	}
    }
}
