#ifndef MAP_HPP_
#define MAP_HPP_

#include <map>
#include <string>
#include <vector>

#include "gfx/component.hpp"
#include "gfx/data_structs.hpp"

namespace map {
const int MAP_ROWS    = 9;
const int MAP_COLUMNS = 16;
enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW_PLAINS };

class Tile {
public:
  Tile();
  Tile(std::string, unsigned, unsigned);

  const data::State_Data&                   get_state() const;
  const component::Renderable_Sprite_Frame& get_renderable_component() const;
  void set_state(const int, const int, const std::string);

private:
  data::State_Data                   state_;
  component::Renderable_Sprite_Frame renderable_component_;
};

class Board {
public:
  Board();

  unsigned    get_column_size() const;
  unsigned    get_row_size() const;
  const Tile* get_tile_at(unsigned, unsigned) const;
  void        set_tile_at(unsigned, unsigned, const std::string);

private:
  void init_board(unsigned, unsigned);
  void map_load();

  unsigned                       columns_;
  unsigned                       rows_;
  std::vector<std::vector<Tile>> board_vector_;
};

}  // namespace map

#endif  // MAP_HPP_
