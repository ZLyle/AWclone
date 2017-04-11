//
// Map bullshit is placed here.
//
#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include "gfx.h"

// Enumerators are types who's values are specfied by the range they're defined
// with. This is fairly apparent, as seen here. It's better to use these than
// some shit like a string when you need to "name" things for comparisons. Also,
// note that there are a few ways to declare enumerators, this is the most
// common. Other ways let you specify enumerations of a specific class/type, and
// an extension of that lets you not name the actual enumerators until later.
//
// These also are, by default, associated with a numerical value that iterates
// as the listing goes on.
enum TileType { PLAINS, MOUNTAIN, FOREST, RIVER, SEA, REEF, SHOAL,
                ROAD, BRIDGE, BUILDING };

enum BuildingType { HQ, CITY, FACTORY, AIRPORT, DOCK };

enum Faction { NEUTRAL, RED, BLUE, YELLOW, GREEN };

// The Building class should (probably) be simply an object that holds the image
// of the building, the faction who controls the building, and the actual kind
// of building it is.
//
// Later on we need to find a way to extend this into implementing the specific
// building type in a way that is flexible. As of now, a city is no different
// than a factory. Eventually we need to have some method that the UI will call
// when they building is selected. Then, depending on the type, an appropriate
// menu/etc will be created where units can be made, or nothing can happen in
// the case of cities and HQs.
//
// The challenge there is deciding if we should use composition or inheritance.
// With inheritance we have a more classic approach of creating a sub-type of
// building, that has all the methods of the Building class + a few more that we
// can vaguely declare but defer the specification to the sub-classes. Using
// composition, we just say that the Building has a sub-type object with it's
// own methods, etc. This is more modular, and technically a better approach for
// allowing immersive behaviors. It's far preferred in roguelikes etc, where you
// might want to grant an object the properties of a crature or something on a
// whim. HOWEVER, this uses a totally different hierarchy. We'd ditch the
// building class, probably tile aswell, and just have an entity (does nothing
// on its own) that simply contains these component objects.
//
// Status: Partially Completed
// Remaining Features:
//    Building specification
//    Menu calls (buying units)
//    Unit creation (flags to define it's state as used for that turn)
//    Capturing (Capping unit should determine the new Faction)
//      Some sort of meter will be needed to measure capturing progress
class Building {
  public:
    Building(BuildingType, Faction);
    ~Building();

// We shouldn't need this, but might be useful in testing. Changing building
// type in-editor should be limited to removing and replacing buildings.
    //void change_building_type(BuildingType);
    void capture(Faction);

  private:
    BuildingType building_type_;
    Faction faction_;
    GfxTexture building_image_;
};

// The Tile class lacks the functional specification of buildings, but poses a
// few more graphical challenges. The only data needed will be the defense
// rating, and walkability (probably). Movement impairment should probably be
// deferred to the unit classes.
//
// The issue with rendering the tiles is basically this: Should the tiles hold
// their own images? And should we have a tile for every orientation or should
// the renderer change this based on adjacent tiles (for roads and shit)? Right
// now, they hold their own images, but this will probably change. The renderer
// will probably change to hold all the possible images, and then decide which
// tiles look like what, rendering as it sees them. Or perhaps it will give the
// tile the image, and just call it as it is needed. This seems better.
//
// We need a similar way to determine which tiles have what data. Inheritance vs
// composition.
//
// Status: Partially Completed
// Remaining Features:
//    Defense Modifiers
//    Figure out that image bullshit
class Tile {
  public:
    Tile(const int, const int, TileType);
    ~Tile();

// Same deal as for Building, we shouldn't need this. Just remove and replace
// to change a tile.
    //void change_tile_type(TileType);
    void add_building(BuildingType, Faction);
    void remove_building();

    const int get_x();
    const int get_y();
    TileType get_tile_type();
    GfxTexture get_image();

    void set_tile_type(TileType);

  private:
    const int x_;
    const int y_;
    TileType tile_type_;
    GfxTexture tile_image_;
    // We use a pointer to the object here since we don't always have a building
    // on a tile. This keeps us from over-allocating memory.
    Building* contained_building_;
};

// The class Map is a collection of Tiles, and acts as an interface through
// which to interact with the Tiles it contains. About all we need to do for it
// is implement the methods that will interact with the tiles within.
//
// Status: Partially Completed
// Remaining Features:
//    Tile getting and setting methods
class Map {
  public:
    Map(const int, const int);
    ~Map();

    Tile* get_tile_at(int, int);

  private:
    // Note that this is a vector of vectors. vector< vector<Tile> >
    std::vector< std::vector<Tile> > map_vector_;
    const int width_;
    const int height_;
};

#endif //MAP_HEADER

