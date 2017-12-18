#include "component.h"

namespace component {
// Renderable
//
Renderable::~Renderable() {}

// Renderable_Sprite_Frame
//
Renderable_Sprite_Frame::~Renderable_Sprite_Frame() {}

void Renderable_Sprite_Frame::render(gfx::Renderer&          renderer,
                                     const gfx::Texture_Map& texture_map,
                                     const gfx::Atlas&       atlas,
                                     const data::State_Data& state) const {
  SDL_Rect source_;
  SDL_Rect target_;

  source_ = (atlas.at(state.key_).source_);

  target_.x = (state.x_) * gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH;
  target_.y = (state.y_) * gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;
  target_.w = gfx::DEST_DIM_FACTOR * gfx::TILE_WIDTH;
  target_.h = gfx::DEST_DIM_FACTOR * gfx::TILE_HEIGHT;

  // printf("copying: (%d, %d) -> (%d, %d)\n", state.x_, state.y_, target_.x,
  // target_.y);
  SDL_RenderCopy(renderer.get(),
                 texture_map.at(atlas.at(state.key_).texture_name_).get(),
                 &source_,
                 &target_);
}

}  // namespace component
