#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include "gfx.h"
#include "map.h"

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
  const int MAP_DISPLAY_COLUMNS = 16;
  const int MAP_DISPLAY_ROWS = 9;
  const int DEST_DIM_FACTOR = 2;
  //sdl, window, renderer, event handler setup
  SDL_Init(SDL_INIT_VIDEO);
  gfx::Window window;
  window.init(TILE_WIDTH  * DEST_DIM_FACTOR * MAP_DISPLAY_COLUMNS,
              TILE_HEIGHT * DEST_DIM_FACTOR * MAP_DISPLAY_ROWS);
  SDL_Renderer* renderer = window.create_renderer();
  SDL_Event event_handler;

  //file finding
  std::string base_path = SDL_GetBasePath();
  std::string tile_sheet_path = "../../res/map_tiles/map_tile_sheet.png";
  
  //sprite sheet setup
  gfx::Texture tile_sprite_sheet_object = gfx::Texture(renderer, base_path + tile_sheet_path);
  SDL_Texture* tile_sprite_sheet_texture = tile_sprite_sheet_object.get_texture();

  //test map setup
  map::Map game_map = map::Map(0, 0);
  game_map.map_load();

  //rendering testing
  gfx::Image_Map atlas_map = gfx::Image_Map();
  SDL_RenderClear(renderer);

  SDL_Rect src_rect;
  SDL_Rect dest_rect;
  dest_rect.w = TILE_WIDTH * DEST_DIM_FACTOR;
  dest_rect.h = TILE_HEIGHT * DEST_DIM_FACTOR;

  for(int x = 0; x < MAP_COLUMNS; ++x)
  {
    for(int y = 0; y < MAP_ROWS; ++y)
    {
      dest_rect.x = x * TILE_WIDTH * DEST_DIM_FACTOR;
      dest_rect.y = y * TILE_HEIGHT * DEST_DIM_FACTOR;
      src_rect = atlas_map.get_src_rect(game_map.get_tile_key_at(x, y));
      SDL_RenderCopy(renderer, tile_sprite_sheet_texture, &src_rect, &dest_rect);
    }
  }
  SDL_RenderPresent(renderer);

  //pause/delay/exiting/etc
  bool quit_flag = false;
  while (!quit_flag)
  {
    while (SDL_PollEvent(&event_handler) != 0)
    {
      switch (event_handler.type)
      {
      case SDL_QUIT:
        quit_flag = true;
      case SDL_KEYDOWN:
        if (event_handler.key.keysym.sym == SDLK_ESCAPE)
        {
          quit_flag = true;
        }
      }
    }
  }
  
  //wrap up
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
