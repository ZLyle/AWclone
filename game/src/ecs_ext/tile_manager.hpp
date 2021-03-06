#ifndef ECX_EXT_TILE_MANAGER_HPP_
#define ECX_EXT_TILE_MANAGER_HPP_

#include <vector>
#include <cstdint>

#include "tile.hpp"
#include "location_system.hpp"
#include "sprite_system.hpp"

namespace ecs {

struct tile_manager {
  // TODO: Probably going to put the call to load from a file in here, and make
  // this a constructor so we don't have to init the matrix and then each tile.
  void init_tile_matrix(const uint32_t width, const uint32_t height) {
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
  void modify_sprite_at(const int32_t x, const int32_t y,
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
    modify_sprite_at(x, y, new_renderer, texture_name,
                     texture_map, tile_name, tile_map);
  }
  // clang-format on

  void prepare_screen_position(ecs::tile& current_tile) {
    ecs::sprite_comp&   sprite = current_tile.sprite_;
    const gfx::sdl_rect source = sprite.source_.at(sprite.current_frame_);

    const auto x = current_tile.location_.x_ * gfx::DEST_DIM_FACTOR * source.w;
    const auto y = current_tile.location_.y_ * gfx::DEST_DIM_FACTOR * source.h;
    ecs::sprite_system::update_screen_position(sprite, x, y);

    const auto w = gfx::DEST_DIM_FACTOR * source.w;
    const auto h = gfx::DEST_DIM_FACTOR * source.h;
    ecs::sprite_system::update_screen_dimensions(sprite, w, h);
  }

  void prepare_render() {
    for (auto& outer_vec : tile_matrix_) {
      for (auto& current_tile : outer_vec) {
        ecs::sprite_system::update_animation(current_tile.sprite_);
        prepare_screen_position(current_tile);
        ecs::sprite_system::render_to_backbuffer(current_tile.sprite_);
      }
    }
  }

private:
  std::vector<std::vector<tile>> tile_matrix_;
};

}  // namespace ecs

#endif  // ECX_EXT_TILE_MANAGER_HPP_
