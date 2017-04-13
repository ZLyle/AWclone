//
//
//

#include "gfx.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//============================================================================
// Texture definitions
//============================================================================

gfx::Texture::Texture(std::string path, SDL_Renderer* renderer)
  : image_width_(0)
  , image_height_(0)
{
  load_image(path, renderer);
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
// find out how to fucking hide renderer
bool gfx::Texture::load_image(std::string path, SDL_Renderer* renderer)
{
  SDL_Texture* image_texture_ = IMG_LoadTexture(renderer, path.c_str());
  if (image_texture_ == NULL)
  {
    printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);
  }

  return image_texture_ != NULL;
}


void gfx::Texture::decon_assister()
{
  if (image_texture_ != NULL)
  {
    SDL_DestroyTexture(image_texture_);
    image_texture_ = NULL;
    image_width_ = 0;
    image_height_ = 0;
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

bool gfx::Window::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    window_ = SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window_ == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
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
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;
    if ((IMG_Init(img_flags) & img_flags) != img_flags)
    {
      printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
