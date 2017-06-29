#include "gfx.h"

namespace gfx
{

  // Init
  //
  Init::Init()
  {
    int sdl_flags = SDL_INIT_VIDEO;
    int img_flags = IMG_INIT_PNG;

    if (SDL_Init(sdl_flags) < 0)
    {
      printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if ((IMG_Init(img_flags) & img_flags) != img_flags)
    {
      printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
  }

  Init::~Init()
  {
    IMG_Quit();
    SDL_Quit();
  }

  // Window
  //
  Window::Window(const int width, const int height)
  {
    window_ = SDL_CreateWindow("Advance(d) Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window_ == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
  }

  Window::~Window()
  {
    SDL_DestroyWindow(window_);
  }

  SDL_Window* Window::get_window() const
  {
    return window_;
  }

  // Texture_Manager
  // should later be moved from gfx probably, to a more file-handling oriented
  // namespace
  //
  // probably need to put this somewhere where it deals with loading files
  //  instead of in gfx
  // useful later probably:
  //SDL_QueryTexture(image_texture_, NULL, NULL, &image_width_, &image_height_);
  SDL_Texture* Texture_Manager::get_texture(std::string texture_handle) const
  {
    return texture_collection_.at(texture_handle);
  }

  void Texture_Manager::load_texture(SDL_Renderer* renderer,std::string texture_handle, std::string path)
  {
    SDL_Texture* image_texture = IMG_LoadTexture(renderer, path.c_str());
    if (image_texture == nullptr)
    {
      printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    texture_collection_.emplace(texture_handle, image_texture);
  }

  // Texture_Atlas
  //
  Texture_Atlas::Texture_Atlas()
  {
    image_map_builder();
  }

  const SDL_Rect* Texture_Atlas::get_src_rect(std::string key) const
  {
    return &image_map_.at(key).source_;
  }

  void Texture_Atlas::image_map_builder()
  {
    image_map_.emplace("sea", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{               0,                0, TILE_WIDTH, TILE_HEIGHT}});

    image_map_.emplace("reef", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{ TILE_WIDTH *  4,                0, TILE_WIDTH, TILE_HEIGHT}});

    image_map_.emplace("plains", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{               0, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

    image_map_.emplace("hill", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{ TILE_WIDTH *  1, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

    image_map_.emplace("shadow_plains", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{ TILE_WIDTH *  2, TILE_HEIGHT *  2, TILE_WIDTH, TILE_HEIGHT}});

    //TODO: solve the mountain placement problem. irregular height is an issue.
    image_map_.emplace("mountain", Texture_Name_And_Source{"tile_sheet",
        SDL_Rect{ TILE_WIDTH * 15, TILE_HEIGHT *  0, TILE_WIDTH, TILE_HEIGHT + 5}});
  }

  // Render_Helper
  // should probably split it up more?
  //
  Render_Helper::Render_Helper(const Window window)
    : renderer_(create_renderer(window))
    , texture_manager_(Texture_Manager())
    , texture_atlas_(Texture_Atlas())
  {
  }

  Render_Helper::~Render_Helper()
  {
    SDL_DestroyRenderer(renderer_);
  }

  void Render_Helper::enqueue_task(const Render_Task task_to_enqueue)
  {
    tasks_to_render_.push(task_to_enqueue);
  }

  void Render_Helper::render_task_queue()
  {
  }

  SDL_Renderer* Render_Helper::get_renderer() const
  {
    return renderer_;
  }

  SDL_Texture* Render_Helper::get_texture(std::string key) const
  {
    return texture_manager_.get_texture(key);
  }

  const SDL_Rect* Render_Helper::get_src_rect(std::string key) const
  {
    return texture_atlas_.get_src_rect(key);
  }

  SDL_Renderer* Render_Helper::create_renderer(const Window window)
  {
    SDL_Renderer* renderer = SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
  }

  void Render_Helper::flip_buffer()
  {
    SDL_RenderPresent(renderer_);
  }

  void Render_Helper::clear()
  {
    SDL_RenderClear(renderer_);
  }

  void Render_Helper::set_draw_color(Uint32 r, Uint32 b, Uint32 g, Uint32 a)
  {
    SDL_SetRenderDrawColor(renderer_, r, b, g, a);
  }

  //
  //
}
