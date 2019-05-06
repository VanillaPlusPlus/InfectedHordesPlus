# InfectedHordesPlus

Infected Hordes Plus is simply a Infected/Zombie horde spawner, which give you the ability to spawn random hordes at specific locations around the map until it reaches a max amount of active horde spawns. You can let them stay alive, and roam, or despawn after a certain time (in seconds).

**Notes:**
Currently there is no custom loot; however, that is currently in the making.
This addon is configurable completely by JSON, and I am willing to add more data into it if you ask nicely.
Check Change Log: [Here](https://github.com/VanillaPlusPlus/InfectedHordesPlus/releases)

## Installation:
- Before you add this mod, you must make sure that you had a profile set for your server, if not than you will not be able to configure the mod, and the mod will not launch correctly.
- If you don't already have them added then add the following to your start up command while changing "ProfileName" to whatever you wish to name the profile folder:
```
-profiles=ProfileName
```

- Subscribe to the project from the [workshop](https://steamcommunity.com/sharedfiles/filedetails/?id=1733084281)
- Launch DayZ Launcher, not SA Launcher, and go to the mods tab.
- Locate Infected Hordes Plus, right click, and click "Open Folder"
- Copy the mod folder to your root server directory.
- Add Key to keys folder, your servers keys folder is located inside of your server root directory, my keys folder is located inside of the folder @InfectedHordesPlus.
- Add mod folders name to -mod start up tag:
```
-mod=@InfectedHordesPlus
```

## Configuration:
- Inside of your profile folder, which should be in the same folder that you set in the installation process with -profiles, open ```InfectedHordesPlus.json``` and changes it's values. The names are self explainitory. If you need any help please join our [discord](https://discord.gg/bkf3u7M).
Have fun.


**Note: If you set lifetime to 0 inside of the json file, hordes will not despawn with a time; however, they will be removed as a valid "horde" when all horde members are killed off, dead bodies are despawned with normal despawn timer. This allows hordes to stick around to get to know the players. ;D**
