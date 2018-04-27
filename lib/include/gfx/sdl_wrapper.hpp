#ifndef GFX_SDL_WRAPPER_HPP_
#define GFX_SDL_WRAPPER_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <cstdint>

namespace gfx {

typedef SDL_Rect sdl_rect; //typedef to conform styles

class sdl_init {
public:
  sdl_init() {
    uint32_t sdl_flags = SDL_INIT_VIDEO;
    int32_t img_flags = IMG_INIT_PNG;

    if (SDL_Init(sdl_flags) < 0) {
      printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if ((IMG_Init(img_flags) & img_flags) != img_flags) {
      printf("SDL_image could not initialize! SDL_image Error: %s\n",
             IMG_GetError());
    }
  }

  ~sdl_init() {
    IMG_Quit();
    SDL_Quit();
  }
};

class sdl_window {
public:
  sdl_window(const int32_t width, const int32_t height) {
    window_ = SDL_CreateWindow("Advance(d) Wars",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);

    if (window_ == nullptr) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
  }

  sdl_window(const sdl_window&) = delete;

  sdl_window(sdl_window&& to_move) noexcept {
    window_         = to_move.window_;
    to_move.window_ = nullptr;
  }

  friend void swap(sdl_window& left, sdl_window& right) {
    std::swap(left.window_, right.window_);
  }

  sdl_window& operator=(sdl_window right) {
    swap(*this, right);
    return *this;
  }

  ~sdl_window() { SDL_DestroyWindow(window_); }

  SDL_Window* get_window() const { return window_; }

private:
  SDL_Window* window_;
};

class sdl_renderer {
public:
  sdl_renderer(const sdl_window& window) : renderer_(create_renderer(window)) {}

  sdl_renderer(const sdl_renderer&) = delete;

  sdl_renderer(sdl_renderer&& to_move) noexcept {
    renderer_         = to_move.renderer_;
    to_move.renderer_ = nullptr;
  }

  friend void swap(sdl_renderer& left, sdl_renderer& right) {
    std::swap(left.renderer_, right.renderer_);
  }

  sdl_renderer& operator=(sdl_renderer right) {
    swap(*this, right);
    return *this;
  }

  ~sdl_renderer() { SDL_DestroyRenderer(renderer_); }

  SDL_Renderer* get() const { return renderer_; }

private:
  SDL_Renderer* create_renderer(const sdl_window& window) {
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    return renderer;
  }

  SDL_Renderer* renderer_;
};

class sdl_texture {
public:
  sdl_texture(const sdl_renderer& renderer, const std::string path) {
    texture_ = IMG_LoadTexture(renderer.get(), path.c_str());
  }

  sdl_texture(const sdl_texture&) = delete;

  sdl_texture(sdl_texture&& to_move) noexcept {
    texture_         = to_move.texture_;
    to_move.texture_ = nullptr;
  }

  friend void swap(sdl_texture& left, sdl_texture& right) {
    std::swap(left.texture_, right.texture_);
  }

  sdl_texture& operator=(sdl_texture right) {
    swap(*this, right);
    return *this;
  }

  ~sdl_texture() { SDL_DestroyTexture(texture_); }

  SDL_Texture* get() const { return texture_; }

private:
  SDL_Texture* texture_;
};

struct render_helper {
  static void render_copy(const sdl_renderer& renderer,
                          const sdl_texture&  texture,
                          const sdl_rect&     source,
                          const sdl_rect&     target) {
    SDL_RenderCopy(renderer.get(), texture.get(), &source, &target);
  }

  static void flip_buffer(const sdl_renderer& renderer) {
    SDL_RenderPresent(renderer.get());
  }

  static void clear(const sdl_renderer& renderer) {
    SDL_RenderClear(renderer.get());
  }

  static void set_draw_color(const sdl_renderer& renderer,
                             const uint8_t       r,
                             const uint8_t       b,
                             const uint8_t       g,
                             const uint8_t       a) {
    SDL_SetRenderDrawColor(renderer.get(), r, b, g, a);
  }
};

typedef std::shared_ptr<sdl_renderer> renderer_ptr;

typedef std::shared_ptr<sdl_texture> texture_ptr;

}  // namespace gfx

#endif  // GFX_SDL_WRAPPER_HPP_
