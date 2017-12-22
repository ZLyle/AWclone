#ifndef ECS_EXT_TEXTURE_SYSTEM_HPP_
#define ECS_EXT_TEXTURE_SYSTEM_HPP_

#include "gfx/sdl_wrapper.hpp"
#include "gfx/texture_map.hpp"
#include "gfx/atlas.hpp"
#include "texture_comp.hpp"
#include "location_comp.hpp"

namespace ecs {
struct texture_system {
  static void replace_renderer(texture_comp&            comp_to_modify,
                               const gfx::renderer_ptr& new_renderer) {
    comp_to_modify.renderer_ = new_renderer;
  }

  static void replace_texture(texture_comp&           comp_to_modify,
                              const gfx::texture_ptr& new_texture) {
    comp_to_modify.texture_ = new_texture;
  }

  static void replace_source(texture_comp&     comp_to_modify,
                             std::string       id,
                             const gfx::atlas& atlas) {
    comp_to_modify.source_ = atlas.data_.at(id).source_;
  }

  static void init(texture_comp&            comp_to_modify,
                   const std::string        tile_name,
                   const std::string        texture_name,
                   const gfx::renderer_ptr& new_renderer,
                   const gfx::texture_map&  source_map,
                   const gfx::atlas&        atlas) {
    replace_renderer(comp_to_modify, new_renderer);
    replace_texture(comp_to_modify, source_map.get_texture_at(texture_name));
    replace_source(comp_to_modify, tile_name, atlas);
  }

  static void render(texture_comp&  comp_to_render,
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

#endif  // ECS_EXT_TEXTURE_SYSTEM_HPP_
