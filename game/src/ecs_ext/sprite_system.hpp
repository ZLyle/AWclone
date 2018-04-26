#ifndef ECS_EXT_SPRITE_SYSTEM_HPP_
#define ECS_EXT_SPRITE_SYSTEM_HPP_

#include <cassert>
#include <cstdint>

#include "gfx/sdl_wrapper.hpp"
#include "gfx/texture_map.hpp"
#include "gfx/atlas.hpp"
#include "sprite_comp.hpp"
#include "location_comp.hpp"

namespace ecs {
struct sprite_system {
  static void replace_renderer(sprite_comp&             comp_to_modify,
                               const gfx::renderer_ptr& new_renderer) {
    assert(new_renderer != nullptr);
    comp_to_modify.renderer_ = new_renderer;
  }

  static void replace_texture(sprite_comp&            comp_to_modify,
                              const gfx::texture_ptr& new_texture) {
    assert(new_texture != nullptr);
    comp_to_modify.texture_ = new_texture;
  }

  static void replace_source(sprite_comp&       comp_to_modify,
                             const std::string& tile_name,
                             const gfx::atlas&  tile_map) {
    // clang-format off
    comp_to_modify.total_frames_
      = tile_map.data_.at(tile_name).total_frames_;
    comp_to_modify.hold_time_
      = tile_map.data_.at(tile_name).hold_time_;
    comp_to_modify.frames_held_
      = 0;
    comp_to_modify.source_
      = tile_map.data_.at(tile_name).source_;
    // clang-format on
  }

  static void init(sprite_comp&             comp_to_modify,
                   const gfx::renderer_ptr& new_renderer,
                   const std::string&       texture_name,
                   const gfx::texture_map&  texture_map,
                   const std::string&       tile_name,
                   const gfx::atlas&        tile_map) {
    replace_renderer(comp_to_modify, new_renderer);
    replace_texture(comp_to_modify, texture_map.get_texture_at(texture_name));
    replace_source(comp_to_modify, tile_name, tile_map);
  }

  static void update_animation(sprite_comp& comp_to_modify) {
    if (comp_to_modify.hold_time_ != 0) {
      if (comp_to_modify.frames_held_ == comp_to_modify.hold_time_) {
        ++comp_to_modify.current_frame_;
        comp_to_modify.current_frame_ %= comp_to_modify.total_frames_ + 1;
        comp_to_modify.frames_held_ = 0;
      }
      ++comp_to_modify.frames_held_;
    }
  }

  static void update_screen_position(sprite_comp&  comp_to_modify,
                                     const int32_t screen_x,
                                     const int32_t screen_y) {
    comp_to_modify.screen_x_ = screen_x;
    comp_to_modify.screen_y_ = screen_y;
  }

  static void update_screen_dimensions(sprite_comp&  comp_to_modify,
                                       const int32_t screen_w,
                                       const int32_t screen_h) {
    comp_to_modify.screen_w_ = screen_w;
    comp_to_modify.screen_h_ = screen_h;
  }

  static void render_to_backbuffer(const ecs::sprite_comp& comp_to_render) {
    const auto& source =
        comp_to_render.source_.at(comp_to_render.current_frame_);

    const gfx::sdl_rect target = {comp_to_render.screen_x_,
                                  comp_to_render.screen_y_,
                                  comp_to_render.screen_w_,
                                  comp_to_render.screen_h_};

    gfx::render_helper::render_copy((*comp_to_render.renderer_.get()),
                                    (*comp_to_render.texture_.get()),
                                    source,
                                    target);
  }
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_SYSTEM_HPP_
