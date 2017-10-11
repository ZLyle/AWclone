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

// Renderer
// manages the lifetime of SDL_Renderer
//
Renderer::Renderer(const Window& window)
    : renderer_(create_renderer(window)) {}

Renderer::~Renderer() { SDL_DestroyRenderer(renderer_); }

SDL_Renderer* Renderer::get() { return renderer_; }

SDL_Renderer* Renderer::create_renderer(const Window& window) {
  SDL_Renderer* renderer =
   SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
  }
  return renderer;
}

// Texture
//
//
Texture::Texture(Renderer& renderer, const std::string path) {
  texture_ = IMG_LoadTexture(renderer.get(), path.c_str());
}

Texture::~Texture() {
  SDL_DestroyTexture(texture_);
}

SDL_Texture* Texture::get() const {
  return texture_;
}

// load_texture
//
// clang-format off
void load_texture_to(Texture_Map& texture_collection,
                     Renderer& renderer,
                     const std::string texture_handle,
                     const std::string path) {
  if (texture_collection.find(texture_handle) == texture_collection.end()) {
    Texture image_texture(renderer, path);

    if (image_texture.get() == nullptr) {
      printf("Unable to create texture from %s! SDL_image Error: %s\n",
             path.c_str(), IMG_GetError());
    }
    texture_collection.emplace(texture_handle, std::move(image_texture));
  }
}

// atlus_builder
//
//
std::map<std::string, Texture_Name_And_Source> atlas_builder() {
  std::map<std::string, Texture_Name_And_Source> atlas;

  atlas.emplace( "sea", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{              0,               0, TILE_WIDTH, TILE_HEIGHT}});

  atlas.emplace("reef", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{TILE_WIDTH *  4,               0, TILE_WIDTH, TILE_HEIGHT}});

  atlas.emplace( "plains", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{              0, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

  atlas.emplace( "hill", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{TILE_WIDTH *  1, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

  atlas.emplace("shadow_plains", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{TILE_WIDTH *  2, TILE_HEIGHT * 2, TILE_WIDTH, TILE_HEIGHT}});

  // TODO: solve the mountain placement problem. irregular height is an issue.
  atlas.emplace("mountain", Texture_Name_And_Source{ "tile_atlas",
    SDL_Rect{TILE_WIDTH * 15, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT + 5}});
  return atlas;
}
// clang-format on

}  // namespace gfx
