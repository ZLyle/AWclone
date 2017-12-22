#ifndef ECS_EXT_NAME_SYSTEM_HPP_
#define ECS_EXT_NAME_SYSTEM_HPP_

#include <string>

#include "name_comp.hpp"

namespace ecs {

struct name_system {
  static void modify(name_comp& comp_to_modify, const std::string new_name) {
    comp_to_modify.name_ = new_name;
  }
};

}

#endif  // ECS_EXT_NAME_SYSTEM_HPP_
