## TODO
#### Core stuff

+ ~~Wrap SDL up with RAII practices, preferably as agnostic as possible.~~
+ Create a tool to generate map files as needed.
    * \(Optional) Maybe figure out a way to run the game headless, so a different frontend (ascii-to-terminal, opengl, etc) can be used.
+ Implement a basic main menu in the game to load maps (and later: more).
    * Maybe just keep the map maker seperate.
+ Implement a data structure to store the map in a file.
+ Neighbor-aware tiling.
+ Begin designing and implementing the interface.
    * Needs a cursor that can move across the map.
    * Needs to be able to call up appropriate menus and sub-menus.
    * Have the cursor display info about the tile and units that is is on.
+ Implement building logic, make the cursor able to select them to call a menu.
+ Start implementing units.
    * Use static composition.
    * Need to add in the basic unit stats, but this should be kept seperate from the logic so it can be easily modified.
    * Store the unit vs unit damage in a lookup table? Maybe something better will present itself.
+ Have buildings create units.
+ Create a basic pathfinding system to move units around obstacles/enemies.
    * Animation interpolation to show units move along the given path.
    * Have this reflected in the display (the bigass arrow that shows where they're going).
+ Add a basic turn system.
    * Reminder: Units should only be able to move once per turn, and reset at the turn start.
    * Reminder: New units are created in a post-move state.
+ Units should die, and be removed.
+ ...

#### ECS Components to consider

+ Sprite components that render themselves. __Implemented, working.__
+ Terrain components that carry terrain data, like movespeed and defense stats.
+ Movement components that carry a movespeed and type (infantry, treads, wheel, air, sea, lander, etc).
+ Health component.
+ Faction component, for buildings. (cool idea? maybe extend to units for converting them mid game ie the monk in AoE2 via custom units?)
+ Weapon component. (maybe interface with the alluded-to table.
+ Extra components for special units like APCs, Landers, etc.
+ ...
