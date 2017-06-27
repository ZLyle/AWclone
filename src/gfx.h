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
  class Sprite;

  typedef struct Render_Info
  {
    const std::string texture_name_;
    const SDL_Rect rect_;
  } Render_Info;

  class Init
  {
    public:
      Init();
      ~Init();
  };

  class Window
  {
    public:
      Window(int, int);
      ~Window();

      SDL_Window* get_window() const;

    private:
      SDL_Window* window_;
  };

  class Renderer
  {
    public:
      Renderer(Window);
      ~Renderer();

      SDL_Renderer* get() const;

      void flip_buffer();
      void clear();
      void copy(Sprite, SDL_Rect, SDL_Rect);
      void set_draw_color(Uint32, Uint32, Uint32, Uint32);

    private:
      SDL_Renderer* renderer_;
  };

  class Sprite
  {
    public:
      // path, xstart, ystart, width, height, animation framecount
      Sprite(Renderer, std::string);
      ~Sprite();

      SDL_Texture* get_texture() const;

    private:
      void load_image(Renderer, std::string);

      SDL_Texture* image_texture_;
      int image_width_;
      int image_height_;
  };

  class Image_Map
  {
    public:
      Image_Map();

      std::string get_texture_name(std::string) const;
      SDL_Rect get_src_rect(std::string) const;

      void image_map_builder();

    private:
      std::map<std::string, Render_Info> image_map_;
  };

  // needs: renderer, atlas_map, renderable shit
  class Context
  {
    public:
      Context();
      ~Context();

      void get() const;

      void prepare();
      // should make a render() signature for every type of renderable thing?
      void render();
  };
}

#endif //GRAPHICS_HEADER
