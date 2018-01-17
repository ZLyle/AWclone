#ifndef UTIL_TIMER_HPP_
#define UTIL_TIMER_HPP_

#include <SDL2/SDL.h>
#include <cstdint>

namespace util {

class timer {
public:
  timer() {
    start_ticks_  = 0;
    paused_ticks_ = 0;
    state_        = STOPPED;
  }

  void start() {
    state_        = STARTED;
    start_ticks_  = SDL_GetTicks();
    paused_ticks_ = 0;
  }

  void stop() {
    state_        = STOPPED;
    start_ticks_  = 0;
    paused_ticks_ = 0;
  }

  void pause() {
    if (state_ == STARTED) {
      state_        = PAUSED;
      paused_ticks_ = SDL_GetTicks() - start_ticks_;
      start_ticks_  = 0;
    }
  }

  void unpause() {
    if (state_ == PAUSED) {
      state_        = PAUSED;
      start_ticks_  = SDL_GetTicks() - paused_ticks_;
      paused_ticks_ = 0;
    }
  }

  Uint32 get_ticks() {
    Uint32 time = 0;

    if (state_ == STARTED) {
      if (state_ == PAUSED) {
        time = paused_ticks_;
      } else {
        time = SDL_GetTicks() - start_ticks_;
      }
    }

    return time;
  }

  bool is_stopped() { return (state_ == STOPPED); }

  bool is_started() { return (state_ == STARTED); }

  bool is_paused() { return (state_ == PAUSED); }

private:
  enum timer_state { STOPPED, STARTED, PAUSED };
  uint32_t    start_ticks_;
  uint32_t    paused_ticks_;
  timer_state state_;
};

}  // namespace util

#endif  // UTIL_TIMER_HPP_
