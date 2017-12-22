#ifndef ECS_EXT_TERRAIN_COMP_HPP_
#define ECS_EXT_TERRAIN_COMP_HPP_

#include <string>

namespace ecs {
//enum tiletype { UNDEFINED, SEA, REEF, PLAINS, HILL, MOUNTAIN, SHADOW_PLAINS };

// probably use this for like movement modifiers
struct terrain_comp {
  std::string terrain_type;
};

}

#endif  // ECS_EXT_TERRAIN_COMP_HPP_
