#ifndef ECS_MANAGER_HPP_
#define ECS_MANAGER_HPP_

/*
#include <set>
#include <cassert>
#include <limits>

#include "config.hpp"
#include "entity.hpp"
#include "component.hpp"

namespace ecs {

class manager {
  std::set<entity> entities;
  entity_id        last_entity_created;

  entity_id create_entity() {
    assert(last_entity_created < std::numeric_limits<entity_id>::max());
    entities.insert(++last_entity_created);
    return last_entity_created;
  }
};

}  // namespace ecs
*/

#endif  // ECS_MANAGER_HPP_
