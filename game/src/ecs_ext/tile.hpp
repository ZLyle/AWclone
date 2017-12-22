#ifndef ECS_EXT_TILE_HPP_
#define ECS_EXT_TILE_HPP_

#include "ecs/entity.hpp"
#include "location_comp.hpp"
#include "sprite_comp.hpp"

namespace ecs {

struct tile : public entity {
  location_comp location_;
  sprite_comp   sprite_;
  //name_comp     name_;
};

}

#endif  // ECS_EXT_TILE_HPP_
