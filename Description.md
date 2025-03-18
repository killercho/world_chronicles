# World Chronicles
An RTS game (star craft like game) with a dynamic weather system that has an active effect on the game board.
This is a document describing the overall feel of the game and will be changed accordingly when ideas change,
need some improvement or a new thing is thought of.
!TRIGGER WARNING! The game is based on real facts and logic, so bonuses like "African-Americans are less likely to be seen during the night or in a heavy storm"
will be used because they make local sense. If you feel offended remember this:
 - The game is just that - a game, and it should be used just for fun;
 - I do not care about your feelings;
 - You should not care about my feelings;
 - No matter how much you cry I am not going to change the systems so you can feel like you saved a life.
If on the other hand you found my logic flawed and can prove it then I will gladly listen and apply the changes that were requested.

# Implementation details
### Engine and language
The engine that will be used to create the game rests on the [raylib library](https://www.raylib.com/). Because of this the
language that will be used will be `C++`. Building the application will be done with `cmake` and `g++`. For now the build target will be Linux
but in the future (if the game gets to there) there will be builds for MAC and Windows.

### GitHub issues
All the progress, issues and new ideas that need to be implemented will be done using the GitHub issues technology.
There more information can be found about what will be done, was already done, or is not being worked on currently and why exactly is that.

### clang-format and cppcheck
Keeping the good code hygiene will be done using the clang-format and cppcheck applications. The configuration for both of them is (or will be) located
in the root of the repository.

### Compiler warnings and errors
Warnings will not be tolerated, and the code will be compiled with pedantic flags to avoid any potential issues that can hide behind "just" a warning.

### Code structure
The code structure will be created and worked on as the project develops. For now the only thing I can say is that the code will try to follow all the
necessary good practices of the OOP principles.

# Units
More units will be added as the game's development progresses. For now only the units that come to mind first will be written.
### Races
The game will have 3 races (even though they can be a little bit racist):
 - African-American (blacks),
 - European (whites),
 - Asian (yellows).
The type of races mimics the 3 races from the game "Tzar" (Asian, European and Arabic).
Like in "Tzar", this game will have different buildings, units and progression depending on the weather system and time of day.
The different types of buildings that each of the races have, are described in the 'Buildings' section.

### Race bonuses
Depend on the time of day (mainly whether it is nighttime or daytime), location (e.g. is the race's main village on a higher place,
is it in a swamp, etc.) and the current weather (e.g. is it raining, sunny, snowing, etc.). Other bonuses are more global and are active during the whole play through.
The bonuses will be written as they are though of during the production of the game (expect them to change frequently).
 - African-American bonuses:
     - During the night, the unit's stealth increases (they become harder to detect);
 - European bonuses:
     - Ships sail 1.25 times faster than the ships of other races
 - Asian bonuses:
     - Better production towards researching science related technologies

### Race negatives
Because the races have different bonuses based on historical and logical consequences the same is applied to the negatives:
 - African-American:
 - European:
     - Production decreases during hot weather
 - Asian:

### Types of units
Most of the values of the stats are not yet ironed out, so they are to be determined during production (TDB).
Each of the units have:
 - Type - what the unit actually is (e.g. Catapult, Spearman, etc.);
 - Race - what race has access to that unit, can be either one of them, a combination of 2 races or just one race;
 - Melee Damage - damage that the unit deals when the target is in melee range, some units can have only melee damage, or no melee damage
for these units there is only one possible attack;
 - Melee Area - area where the unit can use its melee attack
 - Ranged Damage - damage that the unit deals when the target is between the max ranged area and the melee area.
In that range the unit shoots, or does any other kind of ranged attack. That value can be 0 to signal that the unit does not have any ranged attacks;
 - Ranged Area - area where the unit can use its ranged attack (the enemy has to be beyond the melee zone);
 - No Attack Area - zone in neither melee nor ranged attack can be made. Some units do not have such a limitation;
 - Health - health points that the unit has;
 - Defense - the defense points that the unit has. For more information about how defense is applied check the 'Battle' section;
 - Special Abilities - what special abilities does that unit possess. Can be none or more than one.
 - Cost Resources - cost to build in the resources available - in the order that they are described in the 'Resource' section
 - Cost Maintain - cost to maintain a unit during its lifetime - the same order of resources as the one in the cost to make
 - Cost Population - how many population slots does the unit take

| Unit type | Race | Melee Damage | Melee Area | Ranged Damage | Ranged Area | No Attack Area | Health | Defense | Special Abilities | Cost Resources | Cost Maintain | Cost Population |
| --------- | ---- | ------------ | ---------- | ------------- | ----------- | -------------- | ------ | ------- | ----------------- | -------------- | ------------- | --------------- |
| Villager  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               |
| Ranger    | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               |
| Infantry  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               |
| Catapult  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 2               |

### Special abilities breakdown
The special abilities are abilities that the player can use in or out of battle from the UI of the unit. Each of them does a different thing. Some of them
are exclusive to a unit's race, to a common unit that is specifically from this race, or are accessible to more than one unit.

### Special traits
These are normal abilities that each of the unit has to some extent. For each race these traits can have different values for each of the units.
Having 0 on any of the trait values means that the unit does not have that trait.
 - Stealth - units are not visible to the player if a unit with a visibility trait higher than this unit's stealth trait is not nearby
 - Visibility - units are able to uncover more of the map and can see units with lower stealth

### Battle
During the battle the units exchange attacks (each of the units attacks when it gets ready to attack, special abilities act differently).
Each of the attack deals its damage strait to the health points of the enemy unit. From that damage the defense stat is taken out (flat minus)
and the resulting damage is dealt to the unit. (damage dealt = enemy attack points - defense)

# Buildings
More buildings will be added with the progression of development.
| Building type | Race | Ranged Damage | Ranged Area | No Attack Area | Health | Defense | Special Abilities | Technologies Required | Technologies Inside | Cost Build | Cost Maintain |
| ------------- | ---- | ------------- | ----------- | -------------- | ------ | ------- | ----------------- | --------------------- | ------------------- | ---------- | ------------- |
| Castle/Hub    | All  | NONE          | NONE        | NONE           | TBD    | TBD     | TBD               | NONE                  | TBD                 | TBD        | TBD           |

# Technologies
The same implementation as in "Tzar" (researched from a specific building)

# Resources

# Mechanics

# Weather and day changes

# Different locations

# Map generation and fog of war

# Win conditions

# Artwork, sound design and general style

# Multiplier and AI
