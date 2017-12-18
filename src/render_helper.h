#pragma once

#include "component.h"
#include "data_structs.h"
#include "gfx.h"

namespace gfx {
class Render_Helper {
private:
  std::queue<data::Render_Task> tasks_to_render_;

  void render_task_queue(gfx::Renderer&    renderer,
                         gfx::Texture_Map& texture_map,
                         gfx::Atlas&       atlas) {
    while (!tasks_to_render_.empty()) {
      data::Render_Task current_task = tasks_to_render_.front();
      current_task.to_render_.render(
          renderer, texture_map, atlas, current_task.obj_state_);
      tasks_to_render_.pop();
    }
  }

  void flip_buffer(gfx::Renderer& renderer) {
    SDL_RenderPresent(renderer.get());
  }

  void clear(gfx::Renderer& renderer) { SDL_RenderClear(renderer.get()); }

  void
  set_draw_color(gfx::Renderer& renderer, Uint8 r, Uint8 b, Uint8 g, Uint8 a) {
    SDL_SetRenderDrawColor(renderer.get(), r, b, g, a);
  }

public:
  Render_Helper(const gfx::Window& window, gfx::Renderer& renderer) {
    set_draw_color(renderer, 0, 0, 0, 255);
  }

  ~Render_Helper() {}

  void enqueue_task(const data::Render_Task& task_to_enqueue) {
    tasks_to_render_.push(task_to_enqueue);
  }

  void render(gfx::Renderer&    renderer,
              gfx::Texture_Map& texture_map,
              gfx::Atlas&       atlas) {
    clear(renderer);
    render_task_queue(renderer, texture_map, atlas);
    flip_buffer(renderer);
  }
};
}  // namespace gfx
