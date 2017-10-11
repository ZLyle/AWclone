#include "util.h"

namespace util {
// Timer
//
Timer::Timer() {
  start_ticks_ = 0;
  paused_ticks_ = 0;
  state_ = STOPPED;
}

void Timer::start() {
  state_ = STARTED;
  start_ticks_ = SDL_GetTicks();
  paused_ticks_ = 0;
}

void Timer::stop() {
  state_ = STOPPED;
  start_ticks_ = 0;
  paused_ticks_ = 0;
}

void Timer::pause() {
  if (state_ == STARTED) {
    state_ = PAUSED;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
    start_ticks_ = 0;
  }
}

void Timer::unpause() {
  if (state_ == PAUSED) {
    state_ = PAUSED;
    start_ticks_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

Uint32 Timer::get_ticks() {
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

bool Timer::is_stopped() { return (state_ == STOPPED); }

bool Timer::is_started() { return (state_ == STARTED); }

bool Timer::is_paused() { return (state_ == PAUSED); }

}  // namespace util
