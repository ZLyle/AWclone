//
//
//

#include "gfx.h"

SDL_Renderer* gfx_renderer = NULL;

//============================================================================
// GfxTexture definitions
//============================================================================

GfxTexture::GfxTexture()
{
  image_texture = NULL;
  image_width = 0;
  image_height = 0;
}

GfxTexture::~GfxTexture()
{
  free();
}

bool GfxTexture::load_image(std::string path)
{
  free();

  SDL_Texture* new_texture = NULL;
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));

    new_texture = SDL_CreateTextureFromSurface(gfx_renderer, loaded_surface);
    if (new_texture == NULL)
    {
      printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      image_width = loaded_surface->w;
      image_height = loaded_surface->h;
    }

    SDL_FreeSurface(loaded_surface);
  }

  image_texture = new_texture;
  return image_texture != NULL;
}

void GfxTexture::free()
{
  if (image_texture != NULL)
  {
    SDL_DestroyTexture(image_texture);
    image_texture = NULL;
    image_width = 0;
    image_height = 0;
  }
}

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
  SDL_RenderCopy(gfx_renderer, image_texture, clip, &render_quad);
}

int GfxTexture::getWidth()
{
  return image_width;
}

int GfxTexture::getHeight()
{
  return image_height;
}

//============================================================================
//
//============================================================================
