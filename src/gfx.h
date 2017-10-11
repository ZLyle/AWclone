#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <map>
#include <queue>
#include <string>
#include "component.h"
#include "data_structs.h"

namespace gfx {
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;
const int MAP_DISPLAY_COLUMNS = 16;
const int MAP_DISPLAY_ROWS = 9;
const int DEST_DIM_FACTOR = 2;

typedef struct Texture_Name_And_Source {
  const std::string texture_name_;
  const SDL_Rect source_;
} Texture_Name_And_Source;

class Init {
  public:
  Init();
  ~Init();
};

class Window {
  public:
  Window(const int, const int);
  ~Window();

  SDL_Window* get_window() const;

  private:
  SDL_Window* window_;
};

class Texture_Manager {
  public:
  Texture_Manager();

  void load_texture(SDL_Renderer*, std::string, std::string);

  SDL_Texture* get_texture(std::string) const;

  private:
  std::map<std::string, SDL_Texture*> texture_collection_;
};

class Texture_Atlas {
  public:
  Texture_Atlas();

  const SDL_Rect* get_src_rect(std::string) const;
  const std::string get_texture_key(std::string) const;

  void image_map_builder();

  private:
  std::map<std::string, Texture_Name_And_Source> image_map_;
};

class Render_Helper {
  public:
  Render_Helper(const Window&);
  ~Render_Helper();

  void load_texture(std::string, std::string);
  void enqueue_task(const data::Render_Task);
  void render();

  SDL_Renderer* get_renderer();
  SDL_Texture* get_texture(std::string) const;
  const SDL_Rect* get_src_rect(std::string) const;

  private:
  SDL_Renderer* create_renderer(const Window&);
  void render_task_queue();
  void flip_buffer();
  void clear();
  void set_draw_color(Uint8, Uint8, Uint8, Uint8);

  SDL_Renderer* renderer_;
  Texture_Manager texture_manager_;
  Texture_Atlas texture_atlas_;
  std::queue<data::Render_Task> tasks_to_render_;
};
}  // namespace gfx

#endif  // GRAPHICS_HEADER
