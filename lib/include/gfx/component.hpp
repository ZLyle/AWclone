#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>

#include "data_structs.hpp"
#include "gfx.hpp"

namespace component {
class Renderable {
public:
  virtual ~Renderable() {}

  virtual void update(const data::State_Data&) = 0;

  virtual void render(gfx::Renderer&,
                      const gfx::Texture_Map&,
                      const gfx::Atlas&,
                      const data::State_Data&) const = 0;
};

class Renderable_Sprite_Frame : public Renderable {
public:
  ~Renderable_Sprite_Frame() {}

  void update(const data::State_Data& new_data) {
    render_data_ = new_data;
  }

  void render(gfx::Renderer&          renderer,
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

    SDL_RenderCopy(renderer.get(),
                   texture_map.at(atlas.at(state.key_).texture_name_).get(),
                   &source_,
                   &target_);
  }

private:
  data::State_Data render_data_;
};
}  // namespace component

#endif  // COMPONENT_HPP_
