//
//
//

#include "gfx.h"

//============================================================================
// GfxTexture definitions
//============================================================================

gfx::Texture::Texture(std::string path)
{
  load_image(path);
  image_width_ = 0;
  image_height_ = 0;
}

gfx::Texture::~Texture()
{
  free();
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
bool gfx::Texture::load_image(std::string path)
{
  SDL_Renderer* temp_renderer = NULL;
  SDL_Texture* new_texture = NULL;
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));

    new_texture = SDL_CreateTextureFromSurface(temp_renderer, loaded_surface);
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


void gfx::Texture::free()
{
  if (image_texture_ != NULL)
  {
    SDL_DestroyTexture(image_texture_);
    image_texture_ = NULL;
    image_width_ = 0;
    image_height_ = 0;
  }
}

/*
void GfxTexture::render(int x, int y, SDL_Rect* clip)
{
  // Set rendering space
  SDL_Rect render_quad = { x, y, image_width, image_height };

  // Set clip rendering dimensons
  if (clip != NULL)
  {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }

  // Render to screen
  SDL_RenderCopy(gfx::renderer, image_texture, clip, &render_quad);
}
*/

//============================================================================
//
//============================================================================
