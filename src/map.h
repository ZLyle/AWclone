//
// Map bullshit is placed here.
//
#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include <string>
#include <map>
#include "gfx.h"

const int MAP_ROWS = 9;
const int MAP_COLUMNS = 16;

namespace map
{
  enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW_PLAINS };

  class Tile
  {
    public:
      Tile(std::string);

      std::string get_tile_key() const;

    private:
      std::string tile_key_;
  };

  class Board
  {
    public:
      Board();

      map::Tile& get_tile_at(int, int) const;
      void set_tile_at(int, int, TileType);

    private:
      void init_board(int, int);
      void init_tile_collection();
      void map_load();

      std::map<TileType, Tile> tile_collection_;
      std::vector< std::vector<Tile*> > board_vector_;
  };
}

#endif //MAP_HEADER

