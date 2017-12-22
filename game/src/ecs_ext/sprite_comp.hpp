#ifndef ECS_EXT_SPRITE_COMP_HPP_
#define ECS_EXT_SPRITE_COMP_HPP_

#include <memory>
#include <string>

#include "gfx/sdl_wrapper.hpp"
#include "ecs/component.hpp"

namespace ecs {

struct sprite_comp : public component {
  gfx::renderer_ptr renderer_;
  gfx::texture_ptr  texture_;
  gfx::sdl_rect     source_;
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_COMP_HPP_
