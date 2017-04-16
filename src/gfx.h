//
//
//

#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace gfx
{

//SDL_Renderer* renderer = NULL;

  class Texture
  {
    public:
      // path, xstart, ystart, width, height, animation framecount
      Texture(std::string path, SDL_Renderer*);
      ~Texture();

      SDL_Texture* get_texture();
      int get_width();
      int get_height();

    private:
      bool load_image(std::string path, SDL_Renderer*);
      void decon_assister();

      SDL_Texture* image_texture_;
      int image_width_;
      int image_height_;
  };

  class Window
  {
    public:
      Window();
      ~Window();

      bool init();
      // this probably needs to be encapsulated elsewhere asap
      SDL_Renderer* create_renderer();

      int get_width();
      int get_height();

    private:
      void decon_assister();

      SDL_Window* window_;
      int width_;
      int height_;
  };
}

#endif //GRAPHICS_HEADER
