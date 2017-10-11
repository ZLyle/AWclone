#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

#include <string>
#include "data_structs.h"

namespace gfx {
  class Render_Helper;
  class Renderer_Wrapper;
}

namespace component {
class Renderable {
  public:
  virtual ~Renderable() = 0;

  virtual void render(gfx::Renderer_Wrapper&, gfx::Render_Helper&, const data::State_Data&) const = 0;
};

class Renderable_Sprite_Frame : public Renderable {
  public:
  ~Renderable_Sprite_Frame();

  void render(gfx::Renderer_Wrapper&, gfx::Render_Helper&, const data::State_Data&) const;
};
}  // namespace component

#endif  // COMPONENT_HEADER
