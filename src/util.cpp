//
//
//

#include "util.h"

util::Timer::Timer()
{
  start_ticks_ = 0;
  paused_ticks_ = 0;
  state_ = STOPPED;
}

void util::Timer::start()
{
  state_ = STARTED;
  start_ticks_ = SDL_GetTicks();
  paused_ticks_ = 0;
}

void util::Timer::stop()
{
  state_ = STOPPED;
  start_ticks_ = 0;
  paused_ticks_ = 0;
}

void util::Timer::pause()
{
  if (state_ == STARTED)
  {
    state_ = PAUSED;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
    start_ticks_ = 0;
  }
}

void util::Timer::unpause()
{
  if (state_ == PAUSED)
  {
    state_ = PAUSED;
    start_ticks_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

Uint32 util::Timer::get_ticks()
{
  Uint32 time = 0;

  if (state_ == STARTED)
  {
    if (state_ == PAUSED)
    {
      time = paused_ticks_;
    }
    else
    {
      time = SDL_GetTicks() - start_ticks_;
    }
  }

  return time;
}


bool util::Timer::is_stopped()
{
  return (state_ == STOPPED);
}

bool util::Timer::is_started()
{
  return (state_ == STARTED);
}

bool util::Timer::is_paused()
{
  return (state_ == PAUSED);
}

