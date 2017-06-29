#include "component.h"

namespace component
{
  Renderable_Sprite_Frame::~Renderable_Sprite_Frame()
  {
  }

  void Renderable_Sprite_Frame::render(const gfx::Render_Helper* render_helper, const State_Data* state)
  {
    source_ = *(render_helper->get_src_rect(state->key_));
  }
}
