//
// Map bullshit is placed here.
//
#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include <string>
#include "gfx.h"

const int MAP_ROWS = 9;
const int MAP_COLUMNS = 16;

namespace map
{
  enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW };

  class Tile
  {
    public:
      Tile();
      Tile(TileType);

      void set_tile_type(TileType);
      void set_tile_key(std::string);
      TileType get_tile_type();
      std::string get_tile_key();

    private:
      std::string render_info_key_;
      //SDL_Rect src_rect_;
      TileType tile_type_;
  };

  std::string tile_key_assigner(TileType);

  class Map
  {
    public:
      Map(std::string path);
      Map(const int, const int);

      void map_load();
      void set_tile(int, int, TileType);
      TileType get_tile_type_at(int, int);
      std::string get_tile_key_at(int, int);

    private:
      void init_map(int, int);
      std::vector< std::vector<Tile> > map_vector_;
  };
}

#endif //MAP_HEADER

