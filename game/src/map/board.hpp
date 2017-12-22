#ifndef MAP_BOARD_HPP_
#define MAP_BOARD_HPP_

#include <map>
#include <string>
#include <vector>

#include "../ecs_ext/tile_manager.hpp"

namespace map {

const int MAP_ROWS    = 9;
const int MAP_COLUMNS = 16;

void load(ecs::tile_manager&,
          const gfx::renderer_ptr&,
          const gfx::texture_map&,
          const gfx::atlas&);
}

#endif  // MAP_BOARD_HPP_
