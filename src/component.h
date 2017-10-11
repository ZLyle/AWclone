#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

#include <string>
#include "data_structs.h"
#include "gfx.h"


namespace component {
class Renderable {
  public:
  virtual ~Renderable() = 0;

  virtual void render(gfx::Renderer&, const gfx::Texture_Map&,
                      const gfx::Atlas&, const data::State_Data&) const = 0;
};

class Renderable_Sprite_Frame : public Renderable {
  public:
  ~Renderable_Sprite_Frame();

  void render(gfx::Renderer&, const gfx::Texture_Map&, const gfx::Atlas&,
              const data::State_Data&) const;
};
}  // namespace component

#endif  // COMPONENT_HEADER
