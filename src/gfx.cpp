//
//
//

#include "gfx.h"

//============================================================================
// Texture definitions
//============================================================================

gfx::Texture::Texture(SDL_Renderer* renderer, std::string path)
  : image_texture_(nullptr)
  , image_width_(0)
  , image_height_(0)
{
  load_image(renderer, path);
}

//TODO: candidate for removal? I haven't found a case where we need an empty texture
//      since we don't blit onto a texture and then render it
gfx::Texture::Texture(SDL_Renderer* renderer, int width, int height)
  : image_texture_(nullptr)
  , image_width_(width)
  , image_height_(height)
{
  create_empty_texture(renderer, width, height);
}

gfx::Texture::~Texture()
{
  decon_assister();
}

SDL_Texture* gfx::Texture::get_texture()
{
  return image_texture_;
}

int gfx::Texture::get_width()
{
  return image_width_;
}

int gfx::Texture::get_height()
{
  return image_height_;
}

// bool return value currently unused, use it for error checking one day.
//TODO: find out how to fucking hide renderer
bool gfx::Texture::load_image(SDL_Renderer* renderer ,std::string path)
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

bool gfx::Texture::create_empty_texture(SDL_Renderer* renderer, int width, int height)
{
  image_texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
  if (image_texture_ == nullptr)
  {
    printf("Unable to create empty texture! SDL_image Error: %s\n", IMG_GetError());
  }
  else
  {
    printf("SDL_Texture created.\n");
    SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);
  }

  return image_texture_ != nullptr;
}

void gfx::Texture::decon_assister()
{
  if (image_texture_ != nullptr)
  {
    SDL_DestroyTexture(image_texture_);
  }
}

//============================================================================
// Window definitions
//============================================================================

gfx::Window::Window()
  : window_(NULL)
  , width_(0)
  , height_(0)
{
}

gfx::Window::~Window()
{
  decon_assister();
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
      printf("SDL window initialized.\n");
      width_ = SCREEN_WIDTH;
      height_ = SCREEN_HEIGHT;
    }
  }

  return window_ != NULL;
}

SDL_Renderer* gfx::Window::create_renderer()
{
  SDL_Renderer* renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
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

int gfx::Window::get_width()
{
  return width_;
}

int gfx::Window::get_height()
{
  return height_;
}

void gfx::Window::decon_assister()
{
  SDL_DestroyWindow(window_);
}

//============================================================================
// Atlas functions
//============================================================================

gfx::Image_Map::Image_Map()
{
  image_map_builder();
}

std::string gfx::Image_Map::get_texture_name(std::string key)
{
  return (image_map_.at(key).texture_name_);
}

SDL_Rect gfx::Image_Map::get_src_rect(std::string key)
{
  return image_map_.at(key).rect_;
}

// surely there's a better way
void gfx::Image_Map::image_map_builder()
{
  image_map_.emplace("sea_1", Render_Info{"tile_sheet",
      SDL_Rect{               0,                0, TILE_WIDTH, TILE_HEIGHT}});

  image_map_.emplace("reef_1", Render_Info{"tile_sheet",
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





