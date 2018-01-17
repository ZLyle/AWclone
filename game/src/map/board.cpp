#include "board.hpp"

namespace map {

void load(ecs::tile_manager&       manager,
          const gfx::renderer_ptr& renderer,
          const gfx::texture_map&  texture_map,
          const gfx::atlas&        atlas) {
  uint8_t map_array[MAP_ROWS][MAP_COLUMNS] = {
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
  for (uint16_t y = 0; y < MAP_ROWS; ++y) {
    for (uint16_t x = 0; x < MAP_COLUMNS; ++x) {
      switch (map_array[y][x]) {
        case 1:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "sea", atlas);
          break;
        case 2:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "reef", atlas);
          break;
        case 3:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "plains", atlas);
          break;
        case 4:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "hill", atlas);
          break;
        case 5:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "mountain", atlas);
          break;
        case 6:
          manager.init_tile(x, y, renderer, "tile_atlas",
                            texture_map, "shadow_plains", atlas);
          break;
      }
    }
  }
  //clang-format on
}

}  // namespace map
