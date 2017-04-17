#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include "gfx.h"
#include "map.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

/*
void render_tile(map::Tile tile_to_render)
{
}

void render_map()
{
}

void build_test_map()
{
}
*/

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  gfx::Window window;
  window.init();
  SDL_Renderer* renderer = window.create_renderer();
  
  std::string base_path = SDL_GetBasePath();
  std::string tile_sheet_path = "../../res/map_tiles/map_tile_sheet.png";
  
  //gfx::Texture tile_layer = gfx::Texture(renderer, window.get_width(), window.get_height());
  gfx::Texture tile_sprite_sheet_object = gfx::Texture(base_path + tile_sheet_path, renderer);
  SDL_Texture* tile_sprite_sheet_texture = tile_sprite_sheet_object.get_texture();
  SDL_Rect src_rect;
  src_rect.x = 0 * TILE_WIDTH;
  src_rect.y = 2 * TILE_HEIGHT;
  src_rect.w = 1 * TILE_WIDTH;
  src_rect.h = 1 * TILE_HEIGHT;

  SDL_RenderClear(renderer);
  SDL_Rect dest_rect;
  for(int x = 0; x < 16; ++x)
  {
    for(int y = 0; y < 16; ++y)
    {
      dest_rect.x = x * TILE_WIDTH;
      dest_rect.y = y * TILE_HEIGHT;
      dest_rect.w = TILE_WIDTH;
      dest_rect.h = TILE_HEIGHT;
      SDL_RenderCopy(renderer, tile_sprite_sheet_texture, &src_rect, &dest_rect);
    }
  }
  SDL_RenderPresent(renderer);
  
  SDL_Delay(2000);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
