#ifndef ECS_EXT_LOCATION_COMP_HPP_
#define ECS_EXT_LOCATION_COMP_HPP_

#include <cstdint>

#include "ecs/component.hpp"

namespace ecs {

struct location_comp {
  int32_t x_;
  int32_t y_;
};

}  // namespace ecs

#endif  // ECS_EXT_LOCATION_COMP_HPP_
