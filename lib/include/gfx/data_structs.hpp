#ifndef GFX_DATA_STRUCTS_HPP_
#define GFX_DATA_STRUCTS_HPP_

#include <string>

namespace component { class Renderable; }

namespace data {
struct State_Data {
  std::string key_;
  int         x_;
  int         y_;
};

struct Render_Task {
  const State_Data&            obj_state_;
  const component::Renderable& to_render_;
};
}  // namespace data

#endif  // GFX_DATA_STRUCTS_HPP_
