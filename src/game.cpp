#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "gfx.h"
#include "map.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

SDL_Renderer* renderer = NULL;

void render_tile(map::Tile tile_to_render)
{

}

void render_map()
{
}

void build_test_map()
{
}

void create_window(SDL_Window* window)
{
  SDL_Surface* screen_surface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    window = SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
      screen_surface = SDL_GetWindowSurface(window);
      SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0x00, 0xFF));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
  }
}

void destroy_window(SDL_Window* window)
{
  SDL_DestroyWindow(window);
}

int main()
{
  SDL_Window* window = NULL;
  create_window(window);
  SDL_UpdateWindowSurface(window); // <--- Segfault right here, some pointer shit, fix asap

  gfx::Texture test_texture = gfx::Texture("/res/map_tiles/map_tile_sheet.png");
  SDL_Texture* test_image = test_texture.get_texture();

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, test_image, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_Delay(2000);
  destroy_window(window);
  SDL_Quit();
}
