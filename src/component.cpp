#include "component.h"

namespace component
{
  Renderable::~Renderable(){}

  Renderable_Sprite_Frame::~Renderable_Sprite_Frame(){}

  void Renderable_Sprite_Frame::render(gfx::Render_Helper& render_helper, const data::State_Data& state) const
  {
    SDL_Rect source_;
    SDL_Rect target_;
    source_ = *(render_helper.get_src_rect(state.key_));
    target_.x = (state.x_) * gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH ;
    target_.y = (state.y_) * gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;
    target_.w = gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH;
    target_.h = gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;

    //printf("copying: (%d, %d) -> (%d, %d)\n", state->x_, state->y_, target_.x, target_.y);
    SDL_RenderCopy(render_helper.get_renderer(),
                   render_helper.get_texture(state.key_),
                   &source_,
                   &target_);
  }
}
