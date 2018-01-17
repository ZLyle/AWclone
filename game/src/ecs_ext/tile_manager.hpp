#ifndef ECX_EXT_TILE_MANAGER_HPP_
#define ECX_EXT_TILE_MANAGER_HPP_

#include <vector>
#include <cstdint>

#include "tile.hpp"
#include "location_system.hpp"
#include "sprite_system.hpp"

namespace ecs {

struct tile_manager {
  void init(const uint32_t width, const uint32_t height) {
    tile_matrix_.resize(width);
    int32_t x = 0;
    for (auto& inner_vector : tile_matrix_) {
      inner_vector.resize(height);
      int32_t y = 0;
      for (auto& current_tile : inner_vector) {
        ecs::location_system::modify(current_tile.location_, x, y);
        ++y;
      }
      ++x;
    }
  }

  // clang-format off
  void modify_location_at(const int32_t x, const int32_t y) {
    ecs::location_system
       ::modify(tile_matrix_
                  .at(static_cast<uint32_t>(x))
                  .at(static_cast<uint32_t>(y))
                  .location_,
                x,
                y);
  }

  void init_sprite_at(const int32_t x, const int32_t y,
                      const gfx::renderer_ptr& new_renderer,
                      const std::string&       texture_name,
                      const gfx::texture_map&  texture_map,
                      const std::string&       tile_name,
                      const gfx::atlas&        tile_map) {
    ecs::sprite_system
       ::init(tile_matrix_
                .at(static_cast<uint32_t>(x))
                .at(static_cast<uint32_t>(y))
                .sprite_,
              new_renderer,
              texture_name,
              texture_map,
              tile_name,
              tile_map);
  }

  void init_tile(const int32_t x, const int32_t y,
                 const gfx::renderer_ptr& new_renderer,
                 const std::string&       texture_name,
                 const gfx::texture_map&  texture_map,
                 const std::string&       tile_name,
                 const gfx::atlas&        tile_map) {
    modify_location_at(x, y);
    init_sprite_at(x, y, new_renderer, texture_name,
                   texture_map, tile_name, tile_map);
  }
  // clang-format on

  void prepare_render() {
    for (auto& outer_vec : tile_matrix_) {
      for (auto& current_tile : outer_vec) {
        ecs::sprite_system::update_animations(current_tile.sprite_);
        ecs::sprite_system::update_render(current_tile.sprite_,
                                          current_tile.location_);
      }
    }
  }

  std::vector<std::vector<tile>> tile_matrix_;
};

}  // namespace ecs

#endif  // ECX_EXT_TILE_MANAGER_HPP_
