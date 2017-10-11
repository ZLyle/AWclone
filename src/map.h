#ifndef MAP_HEADER
#define MAP_HEADER

#include <map>
#include <string>
#include <vector>
#include "component.h"
#include "data_structs.h"

namespace map {
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 16;
enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW_PLAINS };

class Tile {
  public:
  Tile();
  Tile(std::string, int, int);

  const data::State_Data& get_state() const;
  const component::Renderable_Sprite_Frame& get_renderable_component() const;
  void set_state(const int, const int, const std::string);

  private:
  data::State_Data state_;
  component::Renderable_Sprite_Frame renderable_component_;
};

class Board {
  public:
  Board();

  int get_column_size() const;
  int get_row_size() const;
  const Tile* get_tile_at(int, int) const;
  void set_tile_at(int, int, const std::string);

  private:
  void init_board(int, int);
  void map_load();

  int columns_;
  int rows_;
  std::vector<std::vector<Tile> > board_vector_;
};

}  // namespace map

#endif  // MAP_HEADER
