//
//
//

#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

bool gfx_init();

bool gfx_close();

SDL_Renderer* gfx_renderer;

class GfxTexture {
  public:
    GfxTexture();
    ~GfxTexture();

    bool load_image(std::string path);
    void free();

    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

  private:
    SDL_Texture* image_texture;
    int image_width;
    int image_height;
};

#endif //GRAPHICS_HEADER
