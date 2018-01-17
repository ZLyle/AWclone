#ifndef GFX_ATLAS_HPP_
#define GFX_ATLAS_HPP_

#include <string>
#include <map>
#include <vector>
#include <cstdint>

#include "sdl_wrapper.hpp"
#include "config.hpp"
#include "util/lexical.hpp"

namespace gfx {

struct atlas {
  struct sprite_data {
    const std::string           texture_name_;
    const uint32_t              total_frames_;
    const uint32_t              hold_time_;
    const std::vector<sdl_rect> source_;
  };

  std::map<std::string, sprite_data> data_;

  atlas(std::string path) { load_config(path); }

  void load_config(const std::string& path) {
    std::ifstream input_file_stream(path.c_str(), std::ios::in);

    assert(input_file_stream.is_open());
    assert(input_file_stream.good());

    std::string           key, name, frame_count, hold_time;
    std::vector<sdl_rect> frames;

    do {
      key.clear();
      name.clear();
      frame_count.clear();
      hold_time.clear();
      frames.clear();

      while (input_file_stream.peek() != '{' && input_file_stream.good()) {
        input_file_stream.ignore(STREAM_MAX, '\n');
      }

      input_file_stream.ignore(STREAM_MAX, '\n');  // skip opening brace
      std::getline(input_file_stream >> std::ws, key);
      std::getline(input_file_stream >> std::ws, name);
      std::getline(input_file_stream >> std::ws, frame_count);
      std::getline(input_file_stream >> std::ws, hold_time);
      while (input_file_stream.peek() != '}' && input_file_stream.good()) {
        std::string x, y, w, h;
        std::getline(input_file_stream >> std::ws, x, ',');
        std::getline(input_file_stream >> std::ws, y, ',');
        std::getline(input_file_stream >> std::ws, w, ',');
        std::getline(input_file_stream >> std::ws, h);
        frames.push_back(sdl_rect{util::lexical_cast(x),
                                  util::lexical_cast(y),
                                  util::lexical_cast(w),
                                  util::lexical_cast(h)});
      }
      input_file_stream.ignore(STREAM_MAX, '\n');  // skip closing brace

      data_.emplace(
          key,
          sprite_data{
              name,
              static_cast<uint32_t>(util::lexical_cast(frame_count) - 1),
              static_cast<uint32_t>(util::lexical_cast(hold_time) * TIME_STEP),
              frames});

    } while (input_file_stream.good());
  }
};

}  // namespace gfx

#endif  // GFX_ATLAS_HPP_
