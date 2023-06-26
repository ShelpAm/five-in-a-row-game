#ifndef FIVE_IN_A_ROW_GAME_TIMER_H
#define FIVE_IN_A_ROW_GAME_TIMER_H

#include <chrono>
#include <string>

class Timer {
 public:
  Timer(const char * name);
  Timer(Timer &&) = default;
  Timer(const Timer &) = default;
  Timer & operator=(Timer &&) = delete;
  Timer & operator=(const Timer &) = delete;
  ~Timer();

 private:
  const std::chrono::time_point<std::chrono::high_resolution_clock>
      start_time_point_;
  const std::string name_;
};

#endif  // FIVE_IN_A_ROW_GAME_TIMER_H
