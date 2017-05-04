//
// Map implementations/declarations/etc
//
#include "map.h"

//============================================================================
// Tile definitions
//============================================================================
map::Tile::Tile()
  : tile_type_(UNDEFINED)
{
}

map::Tile::Tile(TileType tile_type)
  : tile_type_(tile_type)
{
  render_info_key_ = tile_key_assigner(tile_type_);
}

void map::Tile::set_tile_type(TileType tile_type)
{
  tile_type_ = tile_type;
  render_info_key_ = tile_key_assigner(tile_type_);
}

map::TileType map::Tile::get_tile_type()
{
  return tile_type_;
}

std::string map::Tile::get_tile_key()
{
  return render_info_key_;
}

// Need to think of a better way to do this shit. Probably going to have a
// blizzard variable that can be 0 or TILE_HEIGHT so if the game is in a
// blizzard state we can just check, set it accordingly, and have the correct
// sprite ripped.
std::string map::tile_key_assigner(map::TileType tile_type)
{
  std::string key_to_return;

  switch (tile_type)
  {
    case UNDEFINED:
      printf("Error, tile_type passed to tile_src_assigner is UNDEFINED!\n"); break;
    case SEA: 
      key_to_return = "sea_1"; break;
    case REEF:
      key_to_return = "reef_1"; break;
    case PLAINS:
      key_to_return = "plains"; break;
    case HILL:
      key_to_return = "hill"; break;
    case SHADOW:
      key_to_return = "shadow_plains"; break;
    case MOUNTAIN:
      key_to_return = "mountain"; break;
  }

  return key_to_return;
}

//============================================================================
// Map definitions
//============================================================================
/*
map::Map::Map(std::string path)
{
}
*/

map::Map::Map(int width, int height)
{
  init_map(width, height);
}

void map::Map::map_load()
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

  init_map(MAP_COLUMNS, MAP_ROWS);

  for(int x = 0; x < MAP_COLUMNS; ++x)
  {
    for(int y = 0; y < MAP_ROWS; ++y)
    {
      switch(map_array[y][x])
      {
        case 1:
          set_tile(x, y, map::SEA);
          break;
        case 2:
          set_tile(x, y, map::REEF);
          break;
        case 3:
          set_tile(x, y, map::PLAINS);
          break;
        case 4:
          set_tile(x, y, map::HILL);
          break;
        case 5:
          set_tile(x, y, map::SHADOW);
          break;
      }
    }
  }
}

void map::Map::set_tile(int x, int y, TileType tile_type)
{
  map_vector_.at(x).at(y).set_tile_type(tile_type);
}

map::TileType map::Map::get_tile_type_at(int x, int y)
{
  return map_vector_.at(x).at(y).get_tile_type();
}

std::string map::Map::get_tile_key_at(int x, int y)
{
  return map_vector_.at(x).at(y).get_tile_key();
}

void map::Map::init_map(int width, int height)
{
  map_vector_.resize(width);
  for (auto& inner_vector : map_vector_)
  {
    inner_vector.resize(height);
  }
}

//============================================================================
//
//============================================================================

