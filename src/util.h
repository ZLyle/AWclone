#pragma once

#include <SDL2/SDL.h>

namespace util {
class Timer {
public:
  Timer();

  void start();
  void stop();
  void pause();
  void unpause();

  Uint32 get_ticks();
  bool   is_stopped();
  bool   is_started();
  bool   is_paused();

private:
  enum timer_state { STOPPED, STARTED, PAUSED };
  Uint32      start_ticks_;
  Uint32      paused_ticks_;
  timer_state state_;
};
}  // namespace util
