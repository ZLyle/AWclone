## Shit to get done
#### Important shit

Note that everything implemented MUST be designed such that it can be extended to include featueres from later games, and maybe our own shit. This kept in a reasonable order, but is subject to change.

+ Implement a data structure to store the map in a file.
    * Need to figure out what the number of tiles are to be possibly stored.
    * (Plains, Mountains, Woods, Rivers, Roads, Bridges, Sea, Reefs, (Pipes?))
    * (HQ, City, Factory, Airport, Port, (Silo?))
+ Create a tool to generate map files as needed.
    * Needs either an ASCII interface or (preferably) something made with SDL.
    * \(Optional) If we use SDL for the map generator, we need to create basic assets.
+ Implement a basic main menu in the game to load maps (and later: more).
    * Possibly make it call the map generator.
+ Use SDL to implement a rendering system for the maps.
    * If we did this for the map generator, probably just bring some of that over via a header.
+ Begin designing and implementing the interface.
    * Needs to be able to call up appropriate menus and sub-menus.
    * Needs a cursor that can move across the map.
    * Have the cursor display info about the tile (and units, later) that is is on.
+ Implement building logic, make the cursor able to select them to call a menu.
+ Start implementing units.
    * Should probably use some form of composition or inheritance to maximize code reuse.
    * Need to add in the basic unit stats, but this should be kept seperate from the logic so it can be easily modified.
    * A Problem that still needs to be worked out: How to store and access the unit vs unit damage easily?
+ Have buildings create units.
+ Add in unit movement and collision.
    * Terrain needs to work correctly. Will need some kind of flags to determine if a unit collides with some terrain.
+ Create a basic pathfinding system to move units around obstacles/enemies.
+ Have this reflected in the display (the bigass arrow that shows where they're going).
+ Add a basic turn system.
    * Buildings should give money on a turn start.
    * Units should only be able to move once per turn, and reset at the turn start.
    * New units are created in a post-move state.
+ Start implementing combat mechanics.
+ Create faction distinctions.
+ Create a way to spawn enemies for testing purposes.
    * (This will probably happen via building selection implementation, so we need a way to restrict what buildings you can access. It could be useful in testing though, as could setting what faction a unit belongs to.)
+ Have movement trigger the option to attack, with menus and all.
+ Have combat logic resolve correctly via the fast-attack shit from the first game (where it skips the animation step).
    * Make sure this checks some setting kept elsewhere, so the user can toggle it to show animations or not.
+ Units should die, and be removed.
+ Implement the ability for allied units to combine to restore health.
+ Implement the ability for infantry to capture buildings.

Add more as you think of it. Placing it in the correct order would be nice.

#### Less important shit

Figure out something for multiplayer.

#### Shit we need units to keep track of

We'll have a table here, probably.
