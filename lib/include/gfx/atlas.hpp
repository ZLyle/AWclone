#ifndef GFX_ATLAS_HPP_
#define GFX_ATLAS_HPP_

#include <string>
#include <map>

#include "sdl_wrapper.hpp"
#include "config.hpp"

namespace gfx {

struct atlas {
  struct texture_name_and_source {
    const std::string texture_name_;
    const sdl_rect    source_;
  };

  std::map<std::string, texture_name_and_source> data_;

  // clang-format off
  atlas() {
    data_.emplace("sea"          , texture_name_and_source{ "tile_atlas",
      sdl_rect{              0,               0, TILE_WIDTH, TILE_HEIGHT}});

    data_.emplace("reef"         , texture_name_and_source{ "tile_atlas",
      sdl_rect{TILE_WIDTH *  4,               0, TILE_WIDTH, TILE_HEIGHT}});

    data_.emplace("plains"       , texture_name_and_source{ "tile_atlas",
      sdl_rect{              0, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

    data_.emplace("hill"         , texture_name_and_source{ "tile_atlas",
      sdl_rect{TILE_WIDTH *  1, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

    data_.emplace("shadow_plains", texture_name_and_source{ "tile_atlas",
      sdl_rect{TILE_WIDTH *  2, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

    // TODO: solve the mountain placement problem. irregular height is an issue.
    data_.emplace("mountain"     , texture_name_and_source{ "tile_atlas",
      sdl_rect{TILE_WIDTH * 15, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT + 5}});
  }
  // clang-format on
};

}

#endif  // GFX_ATLAS_HPP_

