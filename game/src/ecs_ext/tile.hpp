#ifndef ECS_EXT_TILE_HPP_
#define ECS_EXT_TILE_HPP_

#include "ecs/entity.hpp"
#include "location_comp.hpp"
#include "sprite_comp.hpp"

namespace ecs {

struct tile {
  location_comp location_;
  sprite_comp   sprite_;
};

}  // namespace ecs

#endif  // ECS_EXT_TILE_HPP_
