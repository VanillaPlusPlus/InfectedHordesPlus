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

#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\InfectedHordesPlus\\InfectedHordesPlus.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\InfectedHordesPlus\\InfectedHordesPlusConfig.c"


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
                vector spawnPos = config.getHordeZoneLocation();
                if(spawnPos != "0 0 0"){
                    ref InfectedHordesPlus insertHorde = new InfectedHordesPlus(spawnPos, config.getMinInfectedCount(), config.getMaxInfectedCount(), config.getZombieClasses(), config.canSpawnSpecialInfected());
                    m_hordes.Insert(insertHorde);
                    Print("Horde spawned at " + insertHorde.getLocation().ToString() + " " + config.getHordeZoneName(spawnPos));
                    
                    if(config.shouldSendBroadcast()){
                        GetGame().ChatPlayer(1, "Horde has been sighted at " + config.getHordeZoneName(spawnPos));
                    }
                }
            }
        }

        if(m_hordes.Count() == 0){
            lifeTimeClock = 0;
            return;
        }

        if(config.hasLifeTime()){
            foreach(InfectedHordesPlus horde : m_hordes){
                horde.addLifeTime(timeslice);

                if(horde.hasLivedLife(config.getDespawnTime())){
                    Print("Horde spawned at " + horde.getLocation().ToString() + " has lived it's life and depsawned.");
                    horde.deleteHorde();
                    m_hordes.RemoveItem(horde);
                }
            }
        } else{
            foreach(InfectedHordesPlus m_horde : m_hordes){
                if(m_horde.canDespawn()){
                    m_hordes.RemoveItem(m_horde);
                }
            }
        }
    }
}
