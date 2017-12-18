#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <map>
#include <queue>
#include <string>

#include "data_structs.h"

namespace gfx {
const int TILE_WIDTH          = 16;
const int TILE_HEIGHT         = 16;
const int MAP_DISPLAY_COLUMNS = 16;
const int MAP_DISPLAY_ROWS    = 9;
const int DEST_DIM_FACTOR     = 2;

typedef struct Texture_Name_And_Source {
  const std::string texture_name_;
  const SDL_Rect    source_;
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

class Renderer {
public:
  Renderer(const Window&);
  ~Renderer();

  SDL_Renderer* get();

private:
  SDL_Renderer* create_renderer(const Window&);
  SDL_Renderer* renderer_;
};

class Texture {
private:
  SDL_Texture* texture_;

public:
  Texture(Renderer&, const std::string);
  Texture(const Texture&) = delete;
  Texture(Texture&& to_move) noexcept {
    texture_         = to_move.texture_;
    to_move.texture_ = nullptr;
  }
  friend void swap(Texture& left, Texture& right) {
    std::swap(left.texture_, right.texture_);
  }
  Texture& operator=(Texture right) {
    swap(*this, right);
    return *this;
  }
  ~Texture();

  SDL_Texture* get() const;
};

typedef std::map<std::string, Texture> Texture_Map;
void                                   load_texture_to(Texture_Map&,
                                                       Renderer&,
                                                       const std::string,
                                                       const std::string);

typedef std::map<std::string, Texture_Name_And_Source> Atlas;
Atlas                                                  atlas_builder();

}  // namespace gfx
