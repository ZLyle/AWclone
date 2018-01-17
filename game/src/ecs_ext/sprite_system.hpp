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

  static void update_animations(sprite_comp& comp_to_modify) {
    if (comp_to_modify.hold_time_ != 0) {
      if (comp_to_modify.frames_held_ == comp_to_modify.hold_time_) {
        ++comp_to_modify.current_frame_;
        comp_to_modify.current_frame_ %= comp_to_modify.total_frames_ + 1;
        comp_to_modify.frames_held_ = 0;
      }
      ++comp_to_modify.frames_held_;
    }
  }

  static void update_render(const sprite_comp&   comp_to_render,
                            const location_comp& comp_with_target) {
    gfx::sdl_rect source, target;

    source   = comp_to_render.source_.at(comp_to_render.current_frame_);
    // TODO: decouple this shit from the logical location so we can use it
    // for things that aren't logically represented in the game.
    target.x = (comp_with_target.x_) * gfx::DEST_DIM_FACTOR * source.w;
    target.y = (comp_with_target.y_) * gfx::DEST_DIM_FACTOR * source.h;
    target.w = gfx::DEST_DIM_FACTOR * source.w;
    target.h = gfx::DEST_DIM_FACTOR * source.h;

    gfx::render_helper::render_copy((*comp_to_render.renderer_.get()),
                                    (*comp_to_render.texture_.get()),
                                    source,
                                    target);
  }
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_SYSTEM_HPP_
