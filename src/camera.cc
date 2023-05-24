#include "five_in_a_row_game/camera.h"

#include <iostream>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/shader_program.h"
#include "glm/geometric.hpp"

Camera::Camera() {}

void Camera::Update(const float delta_time, const bool keys[256]) {
  front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
  front_.y = sin(glm::radians(pitch_));
  front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
  front_ = glm::normalize(front_);

  position_ += velocity_ * delta_time;
  velocity_ = glm::vec3(0);
  constexpr float speed{15.0f};
  if (keys[GLFW_KEY_W]) velocity_ += front_;
  if (keys[GLFW_KEY_S]) velocity_ -= front_;
  if (keys[GLFW_KEY_A]) velocity_ -= right();
  if (keys[GLFW_KEY_D]) velocity_ += right();
  velocity_ *= speed;
  // std::cout << "Camera position: " << position_.x << " " << position_.y << "
  // "
  // << position_.z << "\n";
  // std::cout << "Camera velocity: " << velocity_.x << " " << velocity_.y << "
  // "
  //           << velocity_.z << "\n";
}
