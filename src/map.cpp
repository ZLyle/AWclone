//
// Map implementations/declarations/etc
//
#include "map.h"

//============================================================================
// Tile definitions
//============================================================================
map::Tile::Tile()
  : src_rect_({0, 0, 0, 0})
  , tile_type_(UNDEFINED)
{
}

map::Tile::Tile(TileType tile_type)
  : tile_type_(tile_type)
{
  src_rect_ = tile_src_assigner(tile_type_);
}

void map::Tile::set_tile_type(TileType tile_type)
{
  tile_type_ = tile_type;
  set_src_rect(tile_src_assigner(tile_type_));
}

map::TileType map::Tile::get_tile_type()
{
  return tile_type_;
}

void map::Tile::set_src_rect(SDL_Rect new_rect)
{
  src_rect_ = tile_src_assigner(tile_type_);
  /*
  src_rect_.x = new_rect.x;
  src_rect_.y = new_rect.y;
  src_rect_.w = new_rect.w;
  src_rect_.h = new_rect.h;
  */
}

SDL_Rect map::Tile::get_src_rect()
{
  return src_rect_;
}

// Need to think of a better way to do this shit. Probably going to have a
// blizzard variable that can be 0 or TILE_HEIGHT so if the game is in a
// blizzard state we can just check, set it accordingly, and have the correct
// sprite ripped.
SDL_Rect map::tile_src_assigner(map::TileType tile_type)
{
  SDL_Rect rect;
  switch (tile_type)
  {
    case UNDEFINED:
      printf("Error, tile_type passed to tile_src_assigner is UNDEFINED!\n");
      break;
    case SEA: 
      rect = {              0,                0, TILE_WIDTH, TILE_HEIGHT};
      break;
    case REEF:
      rect = {TILE_WIDTH *  4,                0, TILE_WIDTH, TILE_HEIGHT};
      break;
    case PLAINS:
      rect = {              0, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT};
      break;
    case HILL:
      rect = {TILE_WIDTH *  1, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT};
      break;
    case SHADOW:
      rect = {TILE_WIDTH *  2, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT};
      break;
      //TODO: solve the mountain placement problem. irregular height is an issue.
    case MOUNTAIN:
      rect = {TILE_WIDTH * 15, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT + 5};
      break;
  }

  return rect;
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
  : width_(width)
  , height_(height)
{
  map_vector_.resize(width);
  for (auto& inner_vector : map_vector_)
  {
    inner_vector.resize(height);
  }
}

//map::Map::~Map() { /* Shouldn't need this, but might.*/ } 

void map::Map::set_tile(int x, int y, TileType tile_type)
{
  map_vector_.at(x).at(y).set_tile_type(tile_type);
}

map::TileType map::Map::get_tile_type(int x, int y)
{
  return map_vector_.at(x).at(y).get_tile_type();
}

SDL_Rect map::Map::get_tile_rect(int x, int y)
{
  return map_vector_.at(x).at(y).get_src_rect();
}

//============================================================================
//
//============================================================================

