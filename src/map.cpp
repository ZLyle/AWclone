//
// Map implementations/declarations/etc
//

#include "map.h"

//============================================================================
// Tile definitions
//============================================================================

map::Tile::Tile(std::string key)
  : tile_key_(key)
{
}

std::string map::Tile::get_tile_key() const
{
  return tile_key_;
}

//============================================================================
// Board definitions
//============================================================================
map::Board::Board()
{
  init_board(0, 0);
  init_tile_collection();
  map_load();
}

map::Tile& map::Board::get_tile_at(int x, int y) const
{
  return *board_vector_.at(x).at(y);
}

void map::Board::set_tile_at(int x, int y, TileType tile_type)
{
  board_vector_.at(x).at(y) = &tile_collection_.at(tile_type);
}

void map::Board::init_board(int width, int height)
{
  board_vector_.resize(width);
  for (std::vector<Tile*> &inner_vector : board_vector_)
  {
    inner_vector.resize(height);
  }
}

// still using the TileType enum for board logic as of now, since tiles may be
// functionally identical but only the renderer thinks they're different (like
// different road directions, etc). Definitely subject to change
void map::Board::init_tile_collection()
{
  tile_collection_.emplace(SEA, Tile("sea"));
  tile_collection_.emplace(REEF, Tile("reef"));
  tile_collection_.emplace(PLAINS, Tile("plains"));
  tile_collection_.emplace(HILL, Tile("hill"));
  tile_collection_.emplace(SHADOW_PLAINS, Tile("shadow_plains"));
  tile_collection_.emplace(MOUNTAIN, Tile("mountain"));
}

void map::Board::map_load()
{

  int map_array[MAP_ROWS][MAP_COLUMNS] =
  {
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 },
    { 1, 2, 1, 3,  3, 4, 5, 3,  3, 3, 3, 3,  3, 3, 3, 3 }
  };

  init_board(MAP_COLUMNS, MAP_ROWS);

  for(int x = 0; x < MAP_COLUMNS; ++x)
  {
    for(int y = 0; y < MAP_ROWS; ++y)
    {
      switch(map_array[y][x])
      {
        case 1:
          set_tile_at(x, y, SEA); break;
        case 2:
          set_tile_at(x, y, REEF); break;
        case 3:
          set_tile_at(x, y, PLAINS); break;
        case 4:
          set_tile_at(x, y, HILL); break;
        case 5:
          set_tile_at(x, y, SHADOW_PLAINS); break;
      }
    }
  }
}
