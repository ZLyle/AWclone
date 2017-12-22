#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
//#include <memory>

#include "gfx/core.hpp"
#include "ecs/core.hpp"
#include "ecs_ext/core.hpp"
#include "map/board.hpp"
#include "util/timer.hpp"

int main() {
  gfx::sdl_init sdl_initializer;

  gfx::sdl_window window(
      gfx::TILE_WIDTH * gfx::DEST_DIM_FACTOR * gfx::MAP_DISPLAY_COLUMNS,
      gfx::TILE_HEIGHT * gfx::DEST_DIM_FACTOR * gfx::MAP_DISPLAY_ROWS);

  gfx::renderer_ptr renderer =
      std::make_shared<gfx::sdl_renderer>(window);

  SDL_Event event_handler;

  // file finding
  std::string base_path       = SDL_GetBasePath();
  std::string tile_sheet_path = "res/map_tiles/map_tile_sheet.png";

  // sprite sheet setup
  gfx::texture_map texture_map;
  texture_map.load_texture(renderer, "tile_atlas", base_path + tile_sheet_path);

  gfx::atlas atlas;

  // test map setup
  ecs::tile_manager game_map = ecs::tile_manager();
  map::load(game_map, renderer, texture_map, atlas);

  // rendering testing
  game_map.render();

  // pause/delay/exiting/etc
  bool quit_flag = false;
  while (!quit_flag) {
    while (SDL_PollEvent(&event_handler) != 0) {
      switch (event_handler.type) {
        case SDL_QUIT: quit_flag = true; [[fallthrough]];
        case SDL_KEYDOWN:
          if (event_handler.key.keysym.sym == SDLK_ESCAPE) {
            quit_flag = true;
          }
      }
    }
  }

  return 0;
}
