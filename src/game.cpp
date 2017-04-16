#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <memory>
#include "gfx.h"
#include "map.h"

/*
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
*/

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

int main()
{
  SDL_Init(SDL_INIT_VIDEO);

  gfx::Window test_window;
  test_window.init();
  SDL_Renderer* renderer = test_window.create_renderer();

  //test_window.update();
  
  std::string base_path = SDL_GetBasePath();
  std::string tile_sheet_path = "../../res/map_tiles/map_tile_sheet.png";
  
  gfx::Texture test_texture = gfx::Texture(base_path + tile_sheet_path, renderer);
  SDL_Texture* test_image = test_texture.get_texture();

  SDL_Rect texture_rect;
  texture_rect.x = 0;
  texture_rect.y = 0;
  texture_rect.w = 256;
  texture_rect.h = 256;

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, test_image, NULL, &texture_rect);
  SDL_RenderPresent(renderer);
  
  SDL_Delay(2000);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
