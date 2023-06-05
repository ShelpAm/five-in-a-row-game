#include "five_in_a_row_game/time.h"

void Time::Update() {
  previous_time_ = current_time_;
  current_time_ = glfwGetTime();
  delta_time_ = current_time_ - previous_time_;
}
