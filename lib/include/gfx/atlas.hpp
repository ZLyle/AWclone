#ifndef GFX_ATLAS_HPP_
#define GFX_ATLAS_HPP_

#include <string>
#include <map>
#include <vector>

#include "sdl_wrapper.hpp"
#include "config.hpp"

namespace gfx {

struct atlas {
  struct sprite_data {
    const std::string           texture_name_;
    const unsigned              total_frames_;
    const unsigned              hold_time_;
    const std::vector<sdl_rect> source_;
  };

  std::map<std::string, sprite_data> data_;

  atlas() { map_atlas(); }

  // clang-format off
  void map_atlas() {
    const unsigned access_offset = 1;
    const int mountain_height = TILE_HEIGHT + 5;

    data_.emplace("sea",
      sprite_data{
        "tile_atlas",
        8 - access_offset,
        TIME_STEP,
        std::vector<sdl_rect>{
          sdl_rect{TILE_WIDTH *  0, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  1, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  2, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  3, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  3, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  2, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  1, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  0, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT}
        }
      });

    data_.emplace("reef",
      sprite_data{
        "tile_atlas",
        8 - access_offset,
        TIME_STEP,
        std::vector<sdl_rect>{
          sdl_rect{TILE_WIDTH *  4, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  5, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  6, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  7, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  7, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  6, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  5, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT},
          sdl_rect{TILE_WIDTH *  4, TILE_HEIGHT *  6, TILE_WIDTH, TILE_HEIGHT}
        }
      });

    data_.emplace("plains",
      sprite_data{
        "tile_atlas",
        1 - access_offset,
        0,
        std::vector<sdl_rect>{
          sdl_rect{TILE_WIDTH *  1, TILE_HEIGHT * 12, TILE_WIDTH, TILE_HEIGHT}
        }
      });

    data_.emplace("hill",
      sprite_data{
        "tile_atlas",
        1 - access_offset,
        0,
        std::vector<sdl_rect>{
        sdl_rect{TILE_WIDTH *  6, TILE_HEIGHT * 10, TILE_WIDTH, TILE_HEIGHT}
        }
      });

    data_.emplace("shadow_plains",
      sprite_data{
        "tile_atlas",
        1 - access_offset,
        0,
        std::vector<sdl_rect>{
          sdl_rect{TILE_WIDTH *  7, TILE_HEIGHT * 10, TILE_WIDTH, TILE_HEIGHT}
        }
      });

    // TODO: solve the mountain placement problem. irregular height is an issue.
    data_.emplace("mountain",
      sprite_data{
        "tile_atlas",
        1 - access_offset,
        0,
        std::vector<sdl_rect>{
          sdl_rect{TILE_WIDTH *  0, (TILE_HEIGHT * 10) - 5,
                   TILE_WIDTH, mountain_height}
        }
      });
  }
  // clang-format on
};

}  // namespace gfx

#endif  // GFX_ATLAS_HPP_
