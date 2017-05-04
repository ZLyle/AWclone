//
//
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

namespace gfx
{
//SDL_Renderer* renderer = NULL;

  class Texture
  {
    public:
      // path, xstart, ystart, width, height, animation framecount
      Texture(SDL_Renderer*, std::string path);
      Texture(SDL_Renderer*, int, int);
      ~Texture();

      SDL_Texture* get_texture();
      int get_width();
      int get_height();

    private:
      bool load_image(SDL_Renderer*, std::string path);
      bool create_empty_texture(SDL_Renderer*, int, int);
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

      bool init(int, int);
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

  typedef struct Render_Info
  {
    std::string texture_name_;
    SDL_Rect rect_;
  } Render_Info;

  class Image_Map
  {
    public:
      Image_Map();
      void image_map_builder();
      std::string get_texture_name(std::string);
      SDL_Rect get_src_rect(std::string);

    private:
      std::map<std::string, Render_Info> image_map_;
  };
}

#endif //GRAPHICS_HEADER
