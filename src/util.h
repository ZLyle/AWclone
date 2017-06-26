//
//
//

#include <SDL2/SDL.h>

#ifndef UTILITY_HEADER
#define UTILITY_HEADER

namespace util
{
  class Timer
  {
    enum timer_state { STOPPED, STARTED, PAUSED };
    public:
      Timer();

      void start();
      void stop();
      void pause();
      void unpause();

      Uint32 get_ticks();
      bool is_stopped();
      bool is_started();
      bool is_paused();

    private:
      Uint32 start_ticks_;
      Uint32 paused_ticks_;
      timer_state state_;
  };
}

#endif //UTILITY_HEADER
