#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include "component.h"
#include "data_structs.h"
#include "gfx.h"
#include "map.h"
#include "util.h"

int main(int argc, char* argv[]) {
  gfx::Init sdl_initializer;
  gfx::Window window = gfx::Window(
   gfx::TILE_WIDTH * gfx::DEST_DIM_FACTOR * gfx::MAP_DISPLAY_COLUMNS,
   gfx::TILE_HEIGHT * gfx::DEST_DIM_FACTOR * gfx::MAP_DISPLAY_ROWS);
  gfx::Render_Helper render_helper(window);
  SDL_Event event_handler;

  // file finding
  std::string base_path = SDL_GetBasePath();
  std::string tile_sheet_path = "../../res/map_tiles/map_tile_sheet.png";

  // sprite sheet setup
  render_helper.load_texture("tile_atlas", base_path + tile_sheet_path);

  // test map setup
  map::Board game_map = map::Board();

  // rendering testing
  data::Render_Task task_to_queue;

  for (int y = 0; y < game_map.get_row_size(); ++y) {
    for (int x = 0; x < game_map.get_column_size(); ++x) {
      task_to_queue = (data::Render_Task){
       game_map.get_tile_at(x, y)->get_state(),
       game_map.get_tile_at(x, y)->get_renderable_component()};
      // printf(" ");
      render_helper.enqueue_task(task_to_queue);
    }
    // printf("\n");
  }
  render_helper.render();

  // pause/delay/exiting/etc
  bool quit_flag = false;
  while (!quit_flag) {
    while (SDL_PollEvent(&event_handler) != 0) {
      switch (event_handler.type) {
        case SDL_QUIT:
          quit_flag = true;
        case SDL_KEYDOWN:
          if (event_handler.key.keysym.sym == SDLK_ESCAPE) {
            quit_flag = true;
          }
      }
    }
  }

  return 0;
}
