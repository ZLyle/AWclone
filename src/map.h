//
// Map bullshit is placed here.
//
#ifndef MAP_HEADER
#define MAP_HEADER

#include <vector>
#include "gfx.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

namespace map
{
  enum TileType { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW };

  class Tile
  {
    public:
      Tile();
      Tile(TileType);

      void set_tile_type(TileType);
      TileType get_tile_type();
      void set_src_rect(SDL_Rect);
      SDL_Rect get_src_rect();

    private:
      SDL_Rect src_rect_;
      TileType tile_type_;
  };

  SDL_Rect tile_src_assigner(TileType);

  class Map
  {
    public:
      Map(std::string path);
      Map(const int, const int);

      //void map_load(std::string path);
      void set_tile(int, int, TileType);
      TileType get_tile_type(int, int);
      SDL_Rect get_tile_rect(int, int);

    private:
      // probably won't need this since we use vectors
      //bool map_free();
      std::vector< std::vector<Tile> > map_vector_;
      const int width_;
      const int height_;
  };
}

#endif //MAP_HEADER

