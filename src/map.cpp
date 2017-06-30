//
// Map implementations/declarations/etc
//

#include "map.h"

namespace map
{

  // Tile
  //
  Tile::Tile()
    : state_({"undefined", 0, 0})
    , renderable_component_()
  {
  }

  const data::State_Data* Tile::get_state() const
  {
    return &state_;
  }

  const component::Renderable_Sprite_Frame* Tile::get_renderable_component() const
  {
    return &renderable_component_;
  }

  void Tile::set_state(const int x, const int y, const std::string key)
  {
    state_ = data::State_Data { key, x, y };
    renderable_component_ = component::Renderable_Sprite_Frame();
  }

  // Board
  //
  Board::Board()
  {
    map_load();
  }

  int Board::get_column_size() const
  {
    return columns_;
  }

  int Board::get_row_size() const
  {
    return rows_;
  }

  const Tile* Board::get_tile_at(int x, int y) const
  {
    return &board_vector_.at(x).at(y);
  }

  void Board::set_tile_at(int x, int y, const std::string key)
  {
    board_vector_.at(x).at(y).set_state(x, y, key);
  }

  void Board::init_board(int width, int height)
  {
    board_vector_.resize(width);
    for (std::vector<Tile> &inner_vector : board_vector_)
    {
      inner_vector.resize(height);
    }
  }

  void Board::map_load()
  {
    int map_array[MAP_ROWS][MAP_COLUMNS] =
    {
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 4, 6,  3, 3, 3, 3,  3, 3, 3, 3 }
    };

    init_board(MAP_COLUMNS, MAP_ROWS);
    rows_ = MAP_ROWS;
    columns_ = MAP_COLUMNS;

    for(int y = 0; y < rows_; ++y)
    {
      for(int x = 0; x < columns_; ++x)
      {
        switch(map_array[y][x])
        {
          case 1:
            set_tile_at(x, y, "sea"); break;
          case 2:
            set_tile_at(x, y, "reef"); break;
          case 3:
            set_tile_at(x, y, "plains"); break;
          case 4:
            set_tile_at(x, y, "hill"); break;
          case 5:
            set_tile_at(x, y, "mountain"); break;
          case 6:
            set_tile_at(x, y, "shadow_plains"); break;
        }
      }
    }
  }

}
