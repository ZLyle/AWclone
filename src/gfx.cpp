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
bool gfx::Texture::load_image(std::string path, SDL_Renderer* renderer)
{
  SDL_Texture* new_texture = NULL;
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (new_texture == NULL)
    {
      printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      image_width_ = loaded_surface->w;
      image_height_= loaded_surface->h;
    }

    SDL_FreeSurface(loaded_surface);
  }

  image_texture_ = new_texture;
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
