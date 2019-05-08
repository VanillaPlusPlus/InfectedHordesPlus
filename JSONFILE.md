# Json Format

This file provide as much information about the JSON config as possible.

| Parameters        | Example Value           | Description  |
| ------------- |:-------------:| -----:|
| maxInfectedCount     | 125 | The max amount of infected in a horde. |
| minInfectedCount | 65 | The minimum amount of infected in a horde. |
| maxHordes | 10 | This is the max amount of total horde allow on the map at one time.|
| spawnTime | 600 | This is the amount of time in seconds it takes for a horde to be spawned |
| depsawnTime | 100 | This is the amount of time in seconds it takes for a horde to be despawned, if set to 0 a horde will only be removed after all infected die.
| canSpawnSpecialInfected | 0 or 1 ONLY | This a true (1), or false (0) for wether or not a translusent Infected will be able to spawn inside of horde.|
| hordePositions | "Middle Of The Map" : [7500, 0, 7500], | This is the array which holds all the locations for the hordes, and where you will add new locations. |


## Adding a new location:

**Goto the bottom of hordePositions:**

```json
        "Vybor": [
            3784,
            0,
            8923
        ],
        "Severograd": [
            8428,
            0,
            12767
        ],
        "Elektro East": [
            10553,
            0,
            2313
        ]
    }
}
```

**Add new location:**

```json
        "Vybor": [
            3784,
            0,
            8923
        ],
        "Severograd": [
            8428,
            0,
            12767
        ],
        "Elektro East": [
            10553,
            0,
            2313
        ],
        "Middle Of Map": [
            7500,
            0,
            7500
        ]
    }
}
```

**Note:**

If you forget a comma before you next position it will not work because of a incorrect syntax. If you add a comma after your last position, you also will throw an error. If you are just simply not good with json formatting: [Go here](https://jsoneditoronline.org/).
