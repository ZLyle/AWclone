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
      Texture(std::string path);
      ~Texture();

      // probably need to implement this soon
      SDL_Texture* get_texture();
      int get_width();
      int get_height();

    private:
      bool load_image(std::string path);
      void free();

      SDL_Texture* image_texture_;
      int frame_count_;
      int image_width_;
      int image_height_;
  };
}

#endif //GRAPHICS_HEADER
