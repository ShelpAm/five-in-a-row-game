#include "five_in_a_row_game/camera.h"

#include <iostream>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/window.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"

Camera::Camera() {}

void Camera::Update(const float delta_time, const bool keys[256]) {
  front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
  front_.y = sin(glm::radians(pitch_));
  front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
  front_ = glm::normalize(front_);

  position_ += velocity_ * delta_time;
  velocity_ = glm::vec3(0);
  constexpr float speed{5.0f};
  if (keys[GLFW_KEY_W]) velocity_ += front_;
  if (keys[GLFW_KEY_S]) velocity_ -= front_;
  if (keys[GLFW_KEY_A]) velocity_ -= right();
  if (keys[GLFW_KEY_D]) velocity_ += right();
  if (keys[GLFW_KEY_LEFT_CONTROL]) velocity_ -= up_;
  if (keys[GLFW_KEY_SPACE]) velocity_ += up_;
  velocity_ *= speed;

  if (static_cast<int>(glm::length(velocity_)) != 0) {
    should_set_position_ = true;
  }
  // std::cout << "Camera position: " << position_.x << " " << position_.y << "
  // "
  // << position_.z << "\n";
  // std::cout << "Camera velocity: " << velocity_.x << " " << velocity_.y << "
  // "
  //           << velocity_.z << "\n";
}

void Camera::SetUniforms(const ShaderProgram & shader_program,
                         const Window & window) {
  if (should_set_position_) {
    shader_program.SetVector3("camera_pos", position_);
    should_set_position_ = false;
  }
  shader_program.SetVector3("spot_light.position", position_);
  shader_program.SetVector3("spot_light.direction", front_);
  shader_program.SetMatrix4("view", view());
  glm::mat4 projection =
      glm::perspective(glm::radians(fov_),
                       (float)window.width() / window.height(), 0.1f, 100.0f);
  shader_program.SetMatrix4("projection", projection);
  // FIXME: 不显示
  auto a = projection * glm::vec4(glm::vec3(0, 0, 5), 1);
}
