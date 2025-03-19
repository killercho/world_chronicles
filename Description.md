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
Most of the values of the stats are not yet ironed out, so they are to be determined during production (TBD).
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
 - Technologies Required - what is required to be researched before the unit can be created
 - Buildings Required - what buildings are required for the unit to be created

| Unit type | Race | Melee Damage | Melee Area | Ranged Damage | Ranged Area | No Attack Area | Health | Defense | Special Abilities | Cost Resources | Cost Maintain | Cost Population | Technologies Required | Buildings Required |
| --------- | ---- | ------------ | ---------- | ------------- | ----------- | -------------- | ------ | ------- | ----------------- | -------------- | ------------- | --------------- | --------------------- | ------------------ |
| Villager  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               | NONE                  | Castle             |
| Ranger    | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               | TBD                   | TBD                |
| Infantry  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 1               | TBD                   | TBD                |
| Catapult  | All  | TBD          | TBD        | TBD           | TBD         | TBD            | TBD    | TBD     | NONE/TBD          | TBD            | TBD           | 2               | TBD                   | TBD                |

### Special abilities breakdown
The special abilities are abilities that the player can use in or out of battle from the UI of the unit. Each of them does a different thing. Some of them
are exclusive to a unit's race, to a common unit that is specifically from this race, or are accessible to more than one unit.

### Special traits
These are special qualities that each of the unit has to some extent, that change the way the unit can be used. For each race these traits can have different values for each of the units.
Having 0 on any of the trait values means that the unit does not have that trait.
Each unit has a random chance to gain a trait when spawning. Some units will always have a trait or a trait boost (boosts the strength of the trait). Some races have a base specific trait base stat
that will be more than 0, thus allowing all the units of the race to benefit from that trait (example is the African-American race having a base stealth trait that linearly boosts that trait of all its units).
 - Stealth - units are not visible to the player if a unit with a visibility trait higher than this unit's stealth trait is not nearby
 - Visibility - units are able to uncover more of the map and can see units with lower stealth

### Battle
During the battle the units exchange attacks (each of the units attacks when it gets ready to attack, special abilities act differently).
Each of the attack deals its damage strait to the health points of the enemy unit. From that damage the defense stat is taken out (flat minus)
and the resulting damage is dealt to the unit. (damage dealt = enemy attack points - defense)

# Buildings
More buildings will be added with the progression of development.
Each of the buildings has a different effect on the economy or population of the kingdom. Some of the buildings can produce units, others can produce resources passively or serve as
a storage for those resources. On the other hand other structures can be used to research new technologies and uncover new units, resources and other buildings. It is not uncommon for
a building to be able to do a combination of those things, leaving the choice of what to prioritize in the hands of the player.
For the buildings that can research and/or spawn units a queue system is implemented that holds the current and next 5 tasks that need to be done. 5 tasks is subject to change during production.
The buildings' main stats are:
 - Building Type - the type of building that it will be;
 - Race - what race can use those buildings;
 - Ranged Damage, Ranged Area, No Attack Area, Health, Defense, Special Abilities, Technologies Required, Costs - same concept as the stats for the units;
 - Technologies Inside - what technologies can be researched from that building once building it was completed

| Building type | Race | Ranged Damage | Ranged Area | No Attack Area | Health | Defense | Special Abilities | Technologies Required | Technologies Inside | Cost Build | Cost Maintain |
| ------------- | ---- | ------------- | ----------- | -------------- | ------ | ------- | ----------------- | --------------------- | ------------------- | ---------- | ------------- |
| Castle/Hub    | All  | NONE          | NONE        | NONE           | TBD    | TBD     | TBD               | NONE                  | TBD                 | TBD        | TBD           |
| Defense tower | All  | TBD           | TBD         | TBD            | TBD    | TBD     | TBD               | TBD                   | TBD                 | TBD        | TBD           |
| House         | All  | NONE          | NONE        | NONE           | TBD    | TBD     | TBD               | NONE                  | TBD                 | TBD        | TBD           |

# Technologies
The same implementation as in "Tzar" (researched from a specific building). Most of the buildings in the game will have access to technologies that can be "researched" for a cost.
During the researching of a technology, no other action can be happening in the same building. For example if a technology is "researched" from the Castle building, then no
units can be created or no new technologies can be researched until this one finishes.

# Resources and eras
Resources can be mined actively (with villagers or other units) or be passively gained by structures.
They have a specific value attached to them and once that value becomes 0, they disappear leaving an empty space on the map. On each map a single resource
of each type is placed where the resource is infinite. This way battles for that resource can take place leaving the winner happy that this specific resource will
be available until the end of the game. For a player to figure out the quantity of the resource, at least one of that resource needs to be harvested.
For example a stone resource's quantity will be unseen until a player's unit has collected at least one of that resource. Once that becomes the case
that resource's (and only that specific rock's) quantity will be seen.
The main resources that are used throughout the game are:
 - Stone;
 - Wood;
 - Gold;
 - Bronze;
 - Iron;
 - Oil;
 - Uranium.
There resources also are used to determine when a kingdom entered a new era. There are 5 eras:
 - Stone era - in that era the player has access only to stone, wood and gold (mainly used for trading and mercenaries);
 - Bronze era - the bronze material is unlocked and the player can make new units and uncover new technologies;
 - Iron era - the iron material is unlocked - new units, new technologies;
 - Industrial era - same thing but for oil
 - Nuclear era - same thing but for uranium. This is the last era of the game.
To enter a new era the player must build a specific building and research the technology that unlocks obtaining the next material.
From the beginning of the game only wood and stone are available, every other material needs to be researched. Whenever a new resource
is researched, a new location is added to the map where that new resource can be mined.

# Trading and mercenaries
When the player has enough gold and has built the appropriate buildings, trading and mercenary hiring can begin.
Trading is used to exchange different resources with the AI marketplace, with other AI or human players. A specific resource can be
exchanged for another specific resource (without itself) or for a flat gold price. Important thing is that for a resource to be able to be exchanged
it needs to be researched first.

The other use of gold is to recruit mercenaries to fight for that kingdom. Mercenaries can be of different races and have different traits
all of this impacting the value of the mercenary. When they are hired they can be used until the unit dies. Besides the traits and races the price is also
affected by the tier of the unit and how far into the technology tree it is.

Other uses for the gold will be determined during the production of the game.

# Weather and day changes
The main gimic of the game is the dynamic weather and day changes. The game will have an active day and night cycle impacting the unit stats
thus becoming a mechanic that needs to be mastered and offering more gameplay flexibility and diversity.
The same can be said about the weather changes. There are a couple of main weather effects that change the stats of the units and affect them
differently depending on the traits and race in a mostly positive way. Besides them there are some extreme weather conditions that impact all the players negatively.
These are mainly disasters connected to the locations on the map. The main weather effects are:
 - Mild weather conditions:
     - Hot weather - pretty self-explanatory;
     - Cold weather - same;
     - Rain - causes rain to fall;
     - Fog;
     - Snowfall;
 - More serious weather conditions:
     - Snow storm;
     - Heat wave;
     - Cyclone - needs more research on how exactly they form;
     - Tornado - happens only on big flat dry areas of land (needs more research on how they form);
     - Tsunami - happens only near large bodies of water, when there was an earthquake or a meteorite fell in the large body of water;
     - River flood - can happen when there was a snow storm followed by a heat wave in a close succession or when there was rain for a while;
     - Earthquake;
     - Meteorite strike;

Only one of these conditions can be active at the same time at the same place. But more that one conditions can be active at the same time on the entirety of the map.
For example there can be a heat wave in the southernmost part of the map and a snow storm at the most northern side of the map.
All of these conditions happen randomly but the chances for them to happen are calculated based on the map and objects that are around the target area.

# Different locations

# Map generation and fog of war

# Win conditions

# Artwork, sound design and general style

# Multiplier and AI
