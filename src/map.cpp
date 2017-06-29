//
// Map implementations/declarations/etc
//

#include "map.h"

namespace map
{

  // Tile
  //
  Tile::Tile()
    : tile_key_(nullptr)
    , tile_renderable_component_(nullptr)
  {
  }

  /*
  Tile::Tile(std::string key, int x, int y)
    : tile_key_(key)
    , tile_renderable_component_(key)
  {
    tile_state_ = { x, y };
  }
  */

  std::string Tile::get_tile_key() const
  {
    return tile_key_;
  }

  void Tile::set_tile_data(int x, int y, std::string key)
  {
    tile_key_ = key;
    tile_state_ = { x, y };
    tile_renderable_component_ = component::Renderable_Sprite_Frame(key);
  }

  // Board
  //
  Board::Board()
  {
    map_load();
  }

  Tile* Board::get_tile_at(int x, int y)
  {
    return &board_vector_.at(x).at(y);
  }

  void Board::set_tile_at(int x, int y, std::string key)
  {
    board_vector_.at(x).at(y).set_tile_data(x, y, key);
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
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 },
      { 1, 2, 1, 3,  3, 4, 5, 6,  3, 3, 3, 3,  3, 3, 3, 3 }
    };

    init_board(MAP_COLUMNS, MAP_ROWS);

    for(int x = 0; x < MAP_COLUMNS; ++x)
    {
      for(int y = 0; y < MAP_ROWS; ++y)
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
