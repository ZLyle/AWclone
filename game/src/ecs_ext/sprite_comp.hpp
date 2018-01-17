#ifndef ECS_EXT_SPRITE_COMP_HPP_
#define ECS_EXT_SPRITE_COMP_HPP_

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

#include "gfx/sdl_wrapper.hpp"
#include "ecs/component.hpp"

namespace ecs {

struct sprite_comp {
  gfx::renderer_ptr          renderer_;
  gfx::texture_ptr           texture_;
  //int                        screen_x_;
  //int                        screen_y_;
  uint32_t                   total_frames_;
  uint32_t                   current_frame_;
  uint32_t                   hold_time_;
  uint32_t                   frames_held_;
  std::vector<gfx::sdl_rect> source_;
};

}  // namespace ecs

#endif  // ECS_EXT_SPRITE_COMP_HPP_
