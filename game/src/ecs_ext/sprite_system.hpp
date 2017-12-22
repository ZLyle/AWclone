#ifndef ECS_EXT_SPRITE_SYSTEM_HPP_
#define ECS_EXT_SPRITE_SYSTEM_HPP_

#include "gfx/sdl_wrapper.hpp"
#include "gfx/texture_map.hpp"
#include "gfx/atlas.hpp"
#include "sprite_comp.hpp"
#include "location_comp.hpp"

namespace ecs {
struct sprite_system {
  static void replace_renderer(sprite_comp&             comp_to_modify,
                               const gfx::renderer_ptr& new_renderer) {
    comp_to_modify.renderer_ = new_renderer;
  }

  static void replace_texture(sprite_comp&            comp_to_modify,
                              const gfx::texture_ptr& new_texture) {
    comp_to_modify.texture_ = new_texture;
  }

  static void replace_source(sprite_comp&      comp_to_modify,
                             std::string       tile_name,
                             const gfx::atlas& tile_map) {
    comp_to_modify.source_ = tile_map.data_.at(tile_name).source_;
  }

  static void init(sprite_comp&            comp_to_modify,
                   const gfx::renderer_ptr& new_renderer,
                   const std::string        texture_name,
                   const gfx::texture_map&  texture_map,
                   const std::string        tile_name,
                   const gfx::atlas&        tile_map) {
    replace_renderer(comp_to_modify, new_renderer);
    replace_texture(comp_to_modify, texture_map.get_texture_at(texture_name));
    replace_source(comp_to_modify, tile_name, tile_map);
  }

  static void render(sprite_comp&   comp_to_render,
                     location_comp& comp_with_target) {
    gfx::sdl_rect source, target;

    source   = comp_to_render.source_;
    target.x = (comp_with_target.x_) * gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH;
    target.y = (comp_with_target.y_) * gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;
    target.w = gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH;
    target.h = gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;

    SDL_RenderCopy((*comp_to_render.renderer_).get(),
                   (*comp_to_render.texture_).get(),
                   &source,
                   &target);
  }
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_SYSTEM_HPP_
