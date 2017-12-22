#include "board.hpp"

namespace map {

const int MAP_ROWS    = 9;
const int MAP_COLUMNS = 16;

void load(ecs::tile_manager&       manager,
          const gfx::renderer_ptr& renderer,
          const gfx::texture_map& map,
          const gfx::atlas&       atlas) {
  int map_array[MAP_ROWS][MAP_COLUMNS] = {
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3},
      {1, 2, 1, 3, 3, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3}};

  manager.init(MAP_COLUMNS, MAP_ROWS);

  // clang-format off
  for (int y = 0; y < MAP_ROWS; ++y) {
    for (int x = 0; x < MAP_COLUMNS; ++x) {
      switch (map_array[y][x]) {
        case 1:
          manager.init_tile(x, y, "sea", "tile_atlas", renderer, map, atlas);
          break;
        case 2:
          manager.init_tile(x, y, "reef", "tile_atlas", renderer, map, atlas);
          break;
        case 3:
          manager.init_tile(x, y, "plains", "tile_atlas", renderer, map, atlas);
          break;
        case 4:
          manager.init_tile(x, y, "hill", "tile_atlas", renderer, map, atlas);
          break;
        case 5:
          manager.init_tile(x, y, "mountain", "tile_atlas",
                            renderer, map, atlas);
          break;
        case 6:
          manager.init_tile(x, y, "shadow_plains", "tile_atlas",
                            renderer, map, atlas);
          break;
      }
    }
  }
  //clang-format on
}

}  // namespace map
