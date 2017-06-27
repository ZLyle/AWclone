//
//
//

#include "gfx.h"

//============================================================================
// Renderer definitions
//============================================================================

SDL_Renderer* gfx::create_renderer(SDL_Window* window)
{
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
  }
  else
  {
    printf("SDL_Renderer created.\n");
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    int img_flags = IMG_INIT_PNG;
    if ((IMG_Init(img_flags) & img_flags) != img_flags)
    {
      printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    else
    {
      printf("SDL_image initialized.\n");
    }
  }

  return renderer;
}

//============================================================================
// Texture definitions
//============================================================================

gfx::Sprite::Sprite(SDL_Renderer* renderer, std::string path)
  : image_texture_(nullptr)
  , image_width_(0)
  , image_height_(0)
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

// bool return value currently unused, use it for error checking one day.
//TODO: find out how to fucking hide renderer
bool gfx::Sprite::load_image(SDL_Renderer* renderer ,std::string path)
{
  image_texture_ = IMG_LoadTexture(renderer, path.c_str());
  if (image_texture_ == nullptr)
  {
    printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    printf("SDL_Texture loaded.\n");
    SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);
  }

  return image_texture_ != nullptr;
}

//============================================================================
// Window definitions
//============================================================================

gfx::Window::Window(int width, int height)
  : window_(NULL)
{
  init(width, height);
}

gfx::Window::~Window()
{
  SDL_DestroyWindow(window_);
}

bool gfx::Window::init(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    printf("SDL initialized.\n");
    window_ = SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window_ == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
      printf("SDL Window created.\n");
      width_ = SCREEN_WIDTH;
      height_ = SCREEN_HEIGHT;
    }
  }

  return window_ != NULL;
}

SDL_Window* gfx::Window::get_window() const
{
  return window_;
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

