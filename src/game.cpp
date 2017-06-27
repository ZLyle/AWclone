#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include "gfx.h"
#include "map.h"
#include "util.h"

int main(int argc, char* argv[])
{
  const int MAP_DISPLAY_COLUMNS = 16;
  const int MAP_DISPLAY_ROWS = 9;
  const int DEST_DIM_FACTOR = 2;
  //sdl, window, renderer, event handler setup
  //SDL_Init(SDL_INIT_VIDEO);
  gfx::Window window = gfx::Window(TILE_WIDTH  * DEST_DIM_FACTOR * MAP_DISPLAY_COLUMNS,
                                   TILE_HEIGHT * DEST_DIM_FACTOR * MAP_DISPLAY_ROWS);
  gfx::Renderer renderer(window);
  SDL_Event event_handler;

  //file finding
  std::string base_path = SDL_GetBasePath();
  std::string tile_sheet_path = "../../res/map_tiles/map_tile_sheet.png";

  //sprite sheet setup
  gfx::Sprite tile_atlas_sprite = gfx::Sprite(renderer, base_path + tile_sheet_path);

  //test map setup
  map::Board game_map = map::Board();

  //rendering testing
  gfx::Image_Map atlas_map = gfx::Image_Map();
  renderer.clear();

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
      src_rect = atlas_map.get_src_rect(game_map.get_tile_at(x, y).get_tile_key());
      renderer.copy(tile_atlas_sprite, src_rect, dest_rect);
    }
  }
  renderer.flip_buffer();

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

  return 0;
}
