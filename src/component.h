#include <string>
#include "gfx.h"

namespace component
{
  // move later
  typedef struct State_Data {
    std::string key_;
    int x_, y_;
  } State_Data;

  class Renderable
  {
    public:
      virtual ~Renderable() = 0;

      virtual void render(const gfx::Render_Helper*, const State_Data*) = 0;
  };

  class Renderable_Sprite_Frame : Renderable
  {
    public:
      ~Renderable_Sprite_Frame();

      void render(const gfx::Render_Helper*, const State_Data*);

    private:
      SDL_Rect source_;
      SDL_Rect target_;
  };
}
