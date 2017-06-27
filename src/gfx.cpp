//
//
//

#include "gfx.h"

//============================================================================
// Init definitions
//============================================================================

gfx::Init::Init()
{
  int sdl_flags = SDL_INIT_VIDEO;
  int img_flags = IMG_INIT_PNG;

  if (SDL_Init(sdl_flags) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  if ((IMG_Init(img_flags) & img_flags) != img_flags)
  {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
  }
}

gfx::Init::~Init()
{
  IMG_Quit();
  SDL_Quit();
}

//============================================================================
// Window definitions
//============================================================================

gfx::Window::Window(int width, int height)
{
  window_ = SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (window_ == NULL)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }
}

gfx::Window::~Window()
{
  SDL_DestroyWindow(window_);
}

SDL_Window* gfx::Window::get_window() const
{
  return window_;
}

//============================================================================
// Renderer definitions
//============================================================================

gfx::Renderer::Renderer(Window window)
{
  SDL_Renderer* renderer = SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
  }
}

gfx::Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer_);
}

SDL_Renderer* gfx::Renderer::get() const
{
  return renderer_;
}

void gfx::Renderer::flip_buffer()
{
  SDL_RenderPresent(renderer_);
}

void gfx::Renderer::clear()
{
  SDL_RenderClear(renderer_);
}

void gfx::Renderer::copy(Sprite sprite, SDL_Rect src_rect, SDL_Rect dest_rect)
{
  SDL_RenderCopy(renderer_, sprite.get_texture(), &src_rect, &dest_rect);
}

void gfx::Renderer::set_draw_color(Uint32 r, Uint32 b, Uint32 g, Uint32 a)
{
  SDL_SetRenderDrawColor(renderer_, r, b, g, a);
}

//============================================================================
// Sprite definitions
//============================================================================

// useful later probably:
//SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);

gfx::Sprite::Sprite(Renderer renderer, std::string path)
{
  load_image(renderer, path);
}

gfx::Sprite::~Sprite()
{
  if (image_texture_ != nullptr)
  {
    SDL_DestroyTexture(image_texture_);
  }
}

SDL_Texture* gfx::Sprite::get_texture() const
{
  return image_texture_;
}

void gfx::Sprite::load_image(Renderer renderer ,std::string path)
{
  image_texture_ = IMG_LoadTexture(renderer.get(), path.c_str());
  if (image_texture_ == nullptr)
  {
    printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
}

//============================================================================
// Atlas functions
//============================================================================

gfx::Image_Map::Image_Map()
{
  image_map_builder();
}

std::string gfx::Image_Map::get_texture_name(std::string key) const
{
  return (image_map_.at(key).texture_name_);
}

SDL_Rect gfx::Image_Map::get_src_rect(std::string key) const
{
  return image_map_.at(key).rect_;
}

// surely there's a better way
void gfx::Image_Map::image_map_builder()
{
  image_map_.emplace("sea", Render_Info{"tile_sheet",
      SDL_Rect{               0,                0, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("reef", Render_Info{"tile_sheet",
      SDL_Rect{ TILE_WIDTH *  4,                0, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("plains", Render_Info{"tile_sheet",
      SDL_Rect{               0, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("hill", Render_Info{"tile_sheet",
      SDL_Rect{ TILE_WIDTH *  1, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("shadow_plains", Render_Info{"tile_sheet",
      SDL_Rect{ TILE_WIDTH *  2, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

  //TODO: solve the mountain placement problem. irregular height is an issue.
  image_map_.emplace("mountain", Render_Info{"tile_sheet",
      SDL_Rect{ TILE_WIDTH * 15, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT + 5}});
}

