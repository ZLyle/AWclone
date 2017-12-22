#ifndef ECS_EXT_TILE_HPP_
#define ECS_EXT_TILE_HPP_

#include "ecs/entity.hpp"
#include "name_comp.hpp"
#include "location_comp.hpp"
#include "texture_comp.hpp"

namespace ecs {

struct tile : public entity {
  location_comp location_;
  texture_comp  texture_;
  name_comp     name_;
};

}

#endif  // ECS_EXT_TILE_HPP_
