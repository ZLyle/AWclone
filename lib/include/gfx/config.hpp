#ifndef GFX_CONFIG_HPP_
#define GFX_CONFIG_HPP_

namespace gfx {

const int TILE_WIDTH          = 16;
const int TILE_HEIGHT         = 16;
const int MAP_DISPLAY_COLUMNS = 16;
const int MAP_DISPLAY_ROWS    = 9;
const int DEST_DIM_FACTOR     = 2;
const int TARGET_FRAME_RATE   = 60;
const int TIME_STEP = static_cast<int>(1000.0f / TARGET_FRAME_RATE);

}  // namespace gfx

#endif  // GFX_CONFIG_HPP_
