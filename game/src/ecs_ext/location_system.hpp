#ifndef ECS_EXT_LOCATION_SYSTEM_HPP_
#define ECS_EXT_LOCATION_SYSTEM_HPP_

#include "location_comp.hpp"

namespace ecs {

struct location_system {
  static void
  modify(logical_location_comp& target, const int new_x, const int new_y) {
    target.x_ = new_x;
    target.y_ = new_y;
  }
};

}  // namespace ecs

#endif  // ECS_EXT_LOCATION_SYSTEM_HPP_
