#ifndef GFX_TEXTURE_MAP_HPP_
#define GFX_TEXTURE_MAP_HPP_

#include <string>
#include <map>
#include <memory>

#include "sdl_wrapper.hpp"

namespace gfx {

struct texture_map {
private:
  std::map<std::string, texture_ptr> texture_map_;

public:
  void load_texture(const renderer_ptr&     renderer,
                    const std::string texture_handle,
                    const std::string path) {
    if (texture_map_.find(texture_handle) == texture_map_.end()) {
      auto image_texture = std::make_shared<sdl_texture>(*renderer, path);

      if (image_texture.get() == nullptr) {
        printf("Unable to create texture from %s! SDL_image Error: %s\n",
               path.c_str(),
               IMG_GetError());
      }
      texture_map_.emplace(texture_handle, image_texture);
    }
  }

  texture_ptr get_texture_at(const std::string id) const {
    return texture_map_.at(id);
  }
};

}  // namespace gfx

#endif  // GFX_TEXTURE_MAP_HPP_
