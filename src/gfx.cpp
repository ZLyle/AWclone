#include "gfx.h"

namespace gfx {
// Init
//
Init::Init() {
  int sdl_flags = SDL_INIT_VIDEO;
  int img_flags = IMG_INIT_PNG;

  if (SDL_Init(sdl_flags) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  if ((IMG_Init(img_flags) & img_flags) != img_flags) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
  }
}

Init::~Init() {
  IMG_Quit();
  SDL_Quit();
}

// Window
//
Window::Window(const int width, const int height) {
  window_ =
   SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (window_ == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }
}

Window::~Window() { SDL_DestroyWindow(window_); }

SDL_Window* Window::get_window() const { return window_; }

// Texture_Manager
// should later be moved from gfx probably, to a more file-handling oriented
// namespace
//
// probably need to put this somewhere where it deals with loading files
//  instead of in gfx
// useful later probably:
// SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);
Texture_Manager::Texture_Manager() {}

SDL_Texture* Texture_Manager::get_texture(std::string texture_handle) const {
  return texture_collection_.at(texture_handle);
}

void Texture_Manager::load_texture(Renderer_Wrapper& renderer,
                                   std::string texture_handle,
                                   std::string path) {
  if (texture_collection_.find(texture_handle) == texture_collection_.end()) {
    SDL_Texture* image_texture = IMG_LoadTexture(renderer.get(), path.c_str());

    if (image_texture == nullptr) {
      printf("Unable to create texture from %s! SDL_image Error: %s\n",
             path.c_str(), IMG_GetError());
    }

    texture_collection_.emplace(texture_handle, image_texture);
  }
}

// Texture_Atlas
//
Texture_Atlas::Texture_Atlas() { image_map_builder(); }

const SDL_Rect* Texture_Atlas::get_src_rect(std::string key) const {
  return &image_map_.at(key).source_;
}

const std::string Texture_Atlas::get_texture_key(std::string object_key) const {
  return image_map_.at(object_key).texture_name_;
}

void Texture_Atlas::image_map_builder() {
  image_map_.emplace(
   "sea", Texture_Name_And_Source{"tile_atlas",
                                  SDL_Rect{0, 0, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("reef", Texture_Name_And_Source{
                              "tile_atlas", SDL_Rect{TILE_WIDTH * 4, 0,
                                                     TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace(
   "plains",
   Texture_Name_And_Source{
    "tile_atlas", SDL_Rect{0, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace(
   "hill", Texture_Name_And_Source{
            "tile_atlas", SDL_Rect{TILE_WIDTH * 1, TILE_HEIGHT * 2, TILE_WIDTH,
                                   TILE_HEIGHT}});

  image_map_.emplace("shadow_plains",
                     Texture_Name_And_Source{
                      "tile_atlas", SDL_Rect{TILE_WIDTH * 2, TILE_HEIGHT * 2,
                                             TILE_WIDTH, TILE_HEIGHT}});

  // TODO: solve the mountain placement problem. irregular height is an issue.
  image_map_.emplace("mountain",
                     Texture_Name_And_Source{
                      "tile_atlas", SDL_Rect{TILE_WIDTH * 15, TILE_HEIGHT * 0,
                                             TILE_WIDTH, TILE_HEIGHT + 5}});
}

// Renderer_Wrapper
// manages the lifetime of SDL_Renderer
//
Renderer_Wrapper::Renderer_Wrapper(const Window& window)
    : renderer_(create_renderer(window)) {}

Renderer_Wrapper::~Renderer_Wrapper() { SDL_DestroyRenderer(renderer_); }

SDL_Renderer* Renderer_Wrapper::get() { return renderer_; }

SDL_Renderer* Renderer_Wrapper::create_renderer(const Window& window) {
  SDL_Renderer* renderer =
   SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
  }
  return renderer;
}

// Render_Helper
// should probably split it up more?
//
Render_Helper::Render_Helper(const Window& window, Renderer_Wrapper& renderer)
    : texture_manager_(Texture_Manager()), texture_atlas_(Texture_Atlas()) {
  set_draw_color(renderer, 0, 0, 0, 255);
}

Render_Helper::~Render_Helper() {}

void Render_Helper::load_texture(Renderer_Wrapper& renderer,
                                 std::string texture_handle, std::string path) {
  texture_manager_.load_texture(renderer, texture_handle, path);
}

void Render_Helper::enqueue_task(const data::Render_Task task_to_enqueue) {
  tasks_to_render_.push(task_to_enqueue);
}

void Render_Helper::render(Renderer_Wrapper& renderer) {
  clear(renderer);
  render_task_queue(renderer);
  flip_buffer(renderer);
}

SDL_Texture* Render_Helper::get_texture(std::string key) const {
  return texture_manager_.get_texture(texture_atlas_.get_texture_key(key));
}

const SDL_Rect* Render_Helper::get_src_rect(std::string key) const {
  return texture_atlas_.get_src_rect(key);
}

void Render_Helper::render_task_queue(Renderer_Wrapper& renderer) {
  while (!tasks_to_render_.empty()) {
    data::Render_Task current_task = tasks_to_render_.front();
    current_task.to_render_->render(renderer, *this, *current_task.obj_state_);
    tasks_to_render_.pop();
  }
}

void Render_Helper::flip_buffer(Renderer_Wrapper& renderer) {
  SDL_RenderPresent(renderer.get());
}

void Render_Helper::clear(Renderer_Wrapper& renderer) {
  SDL_RenderClear(renderer.get());
}

void Render_Helper::set_draw_color(Renderer_Wrapper& renderer, Uint8 r, Uint8 b,
                                   Uint8 g, Uint8 a) {
  SDL_SetRenderDrawColor(renderer.get(), r, b, g, a);
}

}  // namespace gfx
