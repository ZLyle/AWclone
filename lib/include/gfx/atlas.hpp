#ifndef GFX_ATLAS_HPP_
#define GFX_ATLAS_HPP_

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <regex>

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
    std::regex            non_numeric(R"([\D])");
    std::regex            dimensions(R"((\d+),(\d+),(\d+),(\d+))");

    do {
      key.clear();
      name.clear();
      frame_count.clear();
      hold_time.clear();
      frames.clear();

      while (input_file_stream.peek() != '{' && input_file_stream.good()) {
        input_file_stream.ignore(STREAM_MAX, '\n');
      }

      if (!input_file_stream.good()) {
        return;
      }

      input_file_stream.ignore(STREAM_MAX, '\n');  // skip opening brace

      key = util::getline_and_strip_comments(input_file_stream);
      assert(key != "");

      name = util::getline_and_strip_comments(input_file_stream);
      assert(name != "");

      frame_count = util::getline_and_strip_comments(input_file_stream);
      frame_count = std::regex_replace(frame_count, non_numeric, "");
      assert(frame_count != "");

      hold_time = util::getline_and_strip_comments(input_file_stream);
      hold_time = std::regex_replace(hold_time, non_numeric, "");
      assert(hold_time != "");

      while (input_file_stream.peek() != '}' && input_file_stream.good()) {
        std::smatch dim_matches;
        const auto  line = util::getline_and_strip_comments(input_file_stream);
        std::regex_search(line, dim_matches, dimensions);
        assert(dim_matches.size() == 5);

        frames.push_back(sdl_rect{util::lexical_cast<int32_t>(dim_matches[1]),
                                  util::lexical_cast<int32_t>(dim_matches[2]),
                                  util::lexical_cast<int32_t>(dim_matches[3]),
                                  util::lexical_cast<int32_t>(dim_matches[4])});
      }
      input_file_stream.ignore(STREAM_MAX, '\n');  // skip closing brace

      data_.emplace(
          key,
          sprite_data{name,
                      static_cast<uint32_t>(
                          util::lexical_cast<int32_t>(frame_count) - 1),
                      static_cast<uint32_t>(
                          util::lexical_cast<int32_t>(hold_time) * TIME_STEP),
                      frames});

    } while (input_file_stream.good());
  }
};

}  // namespace gfx

#endif  // GFX_ATLAS_HPP_
