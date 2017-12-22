#ifndef ECX_EXT_TILE_MANAGER_HPP_
#define ECX_EXT_TILE_MANAGER_HPP_

#include <vector>

#include "tile.hpp"
#include "name_system.hpp"
#include "location_system.hpp"
#include "sprite_system.hpp"

namespace ecs {

struct tile_manager {
  void init(const unsigned width, const unsigned height) {
    tile_matrix_.resize(width);
    int x = 0;
    for (auto& inner_vector : tile_matrix_) {
      inner_vector.resize(height);
      int y = 0;
      for (auto& current_tile : inner_vector) {
        ecs::location_system::modify(current_tile.location_, x, y);
        ++y;
      }
      ++x;
    }
  }

  // clang-format off
  void modify_name_at(const int x, const int y, const std::string id) {
    ecs::name_system
       ::modify(tile_matrix_
                  .at(static_cast<unsigned>(x))
                  .at(static_cast<unsigned>(y))
                  .name_,
                id);
  }

  void modify_location_at(const int x, const int y) {
    ecs::location_system
       ::modify(tile_matrix_
                  .at(static_cast<unsigned>(x))
                  .at(static_cast<unsigned>(y))
                  .location_,
                x,
                y);
  }

  void init_sprite_at(const int x, const int y,
                      const gfx::renderer_ptr& new_renderer,
                      const std::string        texture_name,
                      const gfx::texture_map&  texture_map,
                      const std::string        tile_name,
                      const gfx::atlas&        tile_map) {
    ecs::sprite_system
       ::init(tile_matrix_
                .at(static_cast<unsigned>(x))
                .at(static_cast<unsigned>(y))
                .sprite_,
              new_renderer,
              texture_name,
              texture_map,
              tile_name,
              tile_map);
  }

  void init_tile(const int x, const int y,
                 const gfx::renderer_ptr& new_renderer,
                 const std::string        texture_name,
                 const gfx::texture_map&  texture_map,
                 const std::string        tile_name,
                 const gfx::atlas&        tile_map) {
    modify_name_at(x, y, tile_name);
    modify_location_at(x, y);
    init_sprite_at(x, y, new_renderer, texture_name,
                   texture_map, tile_name, tile_map);
  }
  // clang-format on

  void render() {
    gfx::sdl_renderer& renderer =
        *(tile_matrix_.at(0).at(0).sprite_.renderer_);
    gfx::render_helper::clear(renderer);

    for (auto& outer_vec : tile_matrix_) {
      for (auto& current_tile : outer_vec) {
        ecs::sprite_system::render(current_tile.sprite_,
                                   current_tile.location_);
      }
    }

    gfx::render_helper::flip_buffer(renderer);
  }

  std::vector<std::vector<tile>> tile_matrix_;
};

}  // namespace ecs

#endif  // ECX_EXT_TILE_MANAGER_HPP_
