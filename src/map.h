//
// Map bullshit is placed here.
//
#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include <string>
#include <map>
#include "gfx.h"
#include "component.h"

const int MAP_ROWS = 9;
const int MAP_COLUMNS = 16;

namespace map
{
  enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW_PLAINS };

  class Tile
  {
    public:
      Tile();
      Tile(std::string, int, int);

      std::string get_tile_key() const;
      void set_tile_data(int, int, std::string);

    private:
      std::string tile_key_;
      component::State_Data tile_state_;
      component::Renderable_Sprite_Frame tile_renderable_component_;
  };

  class Board
  {
    public:
      Board();

      Tile* get_tile_at(int, int);
      void set_tile_at(int, int, std::string);

    private:
      void init_board(int, int);
      void map_load();

      std::vector< std::vector<Tile> > board_vector_;
  };
}

#endif //MAP_HEADER

