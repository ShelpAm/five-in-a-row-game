#include "five_in_a_row_game/timer.h"

#include <chrono>

#include "five_in_a_row_game/logger.h"

Timer::Timer(const char * name)
    : start_time_point_(std::chrono::high_resolution_clock::now()),
      name_(name) {}

Timer::~Timer() {
  const auto end_time_point = std::chrono::high_resolution_clock::now();

  const auto start =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(start_time_point_)
          .time_since_epoch();
  const auto end =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(end_time_point)
          .time_since_epoch();

  const auto duration = end - start;
  Logger::instance().Debug(
      name_ + " time: " + std::to_string(duration.count() * 0.000001) + "ms");
}
