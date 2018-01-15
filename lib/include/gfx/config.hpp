#ifndef GFX_CONFIG_HPP_
#define GFX_CONFIG_HPP_

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include "util/lexical.hpp"

namespace gfx {

const long STREAM_MAX = std::numeric_limits<std::streamsize>::max();

static int TILE_WIDTH  = 16;
static int TILE_HEIGHT = 16;

// default config values
static int TILE_DISPLAY_COLUMNS = 16;
static int TILE_DISPLAY_ROWS    = 9;
static int DEST_DIM_FACTOR      = 2;

// TODO: maybe figure out the timing one day so the user can set this
const int TARGET_FRAME_RATE = 60;
const int TIME_STEP         = static_cast<int>(1000.0f / TARGET_FRAME_RATE);

static void load_gfx_config(std::string path) {
  std::ifstream input_file_stream(path.c_str(), std::ios::in);

  assert(input_file_stream.is_open());
  assert(input_file_stream.good());

  std::string current_setting, current_value;

  do {
    input_file_stream >> std::ws;
    if (input_file_stream.peek() != '#') {
      std::getline(input_file_stream, current_setting, '=');
      std::getline(input_file_stream, current_value); // TODO: improve?

      if (current_setting == "TILE_WIDTH") {
        TILE_WIDTH = util::lexical_cast(current_value);
      } else if (current_setting == "TILE_HEIGHT") {
        TILE_HEIGHT = util::lexical_cast(current_value);
      } else if (current_setting == "TILE_DISPLAY_COLUMNS") {
        TILE_DISPLAY_COLUMNS = util::lexical_cast(current_value);
      } else if (current_setting == "TILE_DISPLAY_ROWS") {
        TILE_DISPLAY_ROWS = util::lexical_cast(current_value);
      } else if (current_setting == "DEST_DIM_FACTOR") {
        DEST_DIM_FACTOR = util::lexical_cast(current_value);
      } else {
        printf("Unknown config setting %s given in gfx_config!\n",
               current_setting.c_str());
      }

    } else {
      input_file_stream.ignore(STREAM_MAX, '\n');
    }
  } while (input_file_stream.good());
}

}  // namespace gfx

#endif  // GFX_CONFIG_HPP_
