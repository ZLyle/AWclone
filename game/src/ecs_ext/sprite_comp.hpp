#ifndef ECS_EXT_SPRITE_COMP_HPP_
#define ECS_EXT_SPRITE_COMP_HPP_

#include <memory>
#include <string>
#include <vector>

#include "gfx/sdl_wrapper.hpp"
#include "ecs/component.hpp"

namespace ecs {

struct sprite_comp : public component {
  gfx::renderer_ptr          renderer_;
  gfx::texture_ptr           texture_;
  unsigned                   total_frames_;
  unsigned                   current_frame_;
  unsigned                   hold_time_;
  unsigned                   frames_held_;
  std::vector<gfx::sdl_rect> source_;
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_COMP_HPP_
