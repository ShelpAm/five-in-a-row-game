#ifndef FIVE_IN_A_ROW_GAME_TIME_H
#define FIVE_IN_A_ROW_GAME_TIME_H

#include "GLFW/glfw3.h"

class Time {
 public:
  Time() = delete;
  Time(Time &&) = default;
  Time(const Time &) = default;
  Time & operator=(Time &&) = default;
  Time & operator=(const Time &) = default;
  ~Time();

  static double current_time() {
    Update();
    return current_time_;
  }
  static double previous_time() {
    Update();
    return previous_time_;
  }
  static double delta_time() {
    Update();
    return delta_time_;
  }

 private:
  static void Update();

 private:
  static inline double current_time_ = 0;
  static inline double previous_time_ = 0;
  static inline double delta_time_ = 0;
};

#endif  // FIVE_IN_A_ROW_GAME_TIME_H
