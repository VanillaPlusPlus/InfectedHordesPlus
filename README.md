# InfectedHordesPlus
A complete server side horde script for DayZ Standalone.

## Installation:
- Download the projects zip file. [Here](https://github.com/VanillaPlusPlus/InfectedHordes/archive/master.zip)
- Uncompress the Zip folder, and move the InfectedHordesPlus folder into the same location where init.c is located.

**Example location:** ```/mpmission/dayzOffline.chernarusplus/```

**Note: If you are using any other mission name other than** ```dayzOffline.chernarusplus```**, you will have to change the includes inside of InfectedHordesPlusSpawner.c to match the name of your mission**

- Inside of your init.c you need to find your MissionServer class.

**By default, it displayed as:** ```class CustomMission : MissionServer```

- Inside of your CustomMission class append the following:
```
	ref InfectedHordesPlusSpawner infectedHordes;
	void CustomMission(){
		infectedHordes = new InfectedHordesPlusSpawner();
	}

	override void OnUpdate(float timeslice){
		super.OnUpdate(timeslice);

		infectedHordes.onUpdate(timeslice);
	}
```

**Note: If you already have override void OnUpdate, and void CustomMission written you can add the following code in the following locations:**

- Above void CustomMission()
```
ref InfectedHordesPlusSpawner infectedHordes;
```

- Inside of void CustomMission()
```
infectedHordes = new InfectedHordesPlusSpawner();
```

- Inside of void OnUpdate()
```
infectedHordes.onUpdate();
```

