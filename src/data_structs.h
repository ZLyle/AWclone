#ifndef DATA_STRUCTS
#define DATA_STRUCTS

#include <string>

namespace component { class Renderable; }
namespace gfx { class Render_Helper; }

namespace data
{
  typedef struct State_Data {
    std::string key_;
    int x_, y_;
  } State_Data;

  typedef struct Render_Task
  {
    const State_Data* obj_state_;
    const component::Renderable* to_render_;
  } Render_Task;
}


#endif //DATA_STRUCTS
