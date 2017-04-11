//
// Map implementations/declarations/etc
//
#include "map.h"

//============================================================================
// Building definitions
//============================================================================
Building::Building(BuildingType building_type, Faction faction)
  : building_type_(building_type)
  , faction_(faction)
{
}

Building::~Building() { /* Shouldn't need this, but might.*/ }

/*
void Building::change_building_type(BuildingType building_type)
{
  this->building_type_ = building_type;
}
*/

void Building::capture(Faction faction)
{
  this->faction_ = faction;
}

//============================================================================
// Tile definitions
//============================================================================
Tile::Tile(int x, int y, TileType tile_type)
  : x_(x)
  , y_(y)
  , tile_type_(tile_type)
{
  contained_building_ = NULL;
}

Tile::~Tile()
{
// EXTREMELY IMPORTANT MY DUDE: every time you use the keyword 'new', you want
// to 'delete' that thing eventually!!! Not doing this creates memory leaks.
  remove_building();
}

/*
void Tile::change_tile_type(TileType tile_type)
{
  this->tile_type_ = tile_type;
}
*/

// Normally we'd want to change an object's properties, but since a tile might
// not always have one of these, it seems better to just have a way to add and
// remove buildings.
void Tile::add_building(BuildingType building_type, Faction faction)
{
  remove_building();
  contained_building_ = new Building(building_type, faction);
}

void Tile::remove_building()
{
  if (contained_building_ != NULL)
  {
    delete &contained_building_;
  }
}

const int Tile::get_x()
{
  return x_;
}

const int Tile::get_y()
{
  return y_;
}

TileType Tile::get_tile_type()
{
  return tile_type_;
}

GfxTexture Tile::get_image()
{
  return tile_image_;
}

void Tile::set_tile_type(TileType tile_type)
{
  tile_type_ = tile_type;
}
//============================================================================
// Map definitions
//============================================================================
Map::Map(int width, int height) : width_(width), height_(height)
{
  map_vector_.resize(width);
  for (auto& inner_vector : map_vector_)
  {
    inner_vector.resize(height);
  }
}

Map::~Map() { /* Shouldn't need this, but might.*/ } 

// In theory this should return a pointer to the Tile at x, y so that we can
// work with it directly. Such as: get_tile_at(5, 5).add_building(HQ, RED)
Tile* Map::get_tile_at(int x, int y)
{
  return &map_vector_.at(x).at(y);
}

//============================================================================
//
//============================================================================

