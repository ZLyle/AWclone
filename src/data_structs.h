#ifndef DATA_STRUCTS
#define DATA_STRUCTS

#include <string>

namespace component { class Renderable; }

namespace data
{
    struct State_Data {
    std::string key_;
    int x_, y_;
  };

  struct Render_Task
  {
    const State_Data& obj_state_;
    const component::Renderable& to_render_;
  };
}

#endif //DATA_STRUCTS
