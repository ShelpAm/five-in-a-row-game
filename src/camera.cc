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

void Camera::Update(const float delta_time, const bool keys[512]) {
  UpdateDirections(delta_time);
  UpdatePosition(delta_time);
  UpdateVelocity(delta_time, keys);
  UpdateCaches(delta_time, keys);
  // std::cout << "Camera position: " << position_.x << " " << position_.y << "
  // "
  //           << position_.z << "\n";
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
  // Because every object has different position, we need to send the model to
  // the shader later.
  // shader_.SetMatrix4("model", glm::mat4(1.0f));
  shader_program.SetMatrix4("view", view());
  glm::mat4 projection =
      glm::perspective(glm::radians(fov_),
                       (float)window.width() / window.height(), 0.1f, 100.0f);
  shader_program.SetMatrix4("projection", projection);
}
void Camera::UpdateDirections(const float delta_time) {
  front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
  front_.y = sin(glm::radians(pitch_));
  front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
  front_ = glm::normalize(front_);
}
void Camera::UpdateVelocity(const float delta_time, const bool keys[512]) {
  velocity_ = glm::vec3(0);
  constexpr float speed{5.0f};
  if (keys[GLFW_KEY_W]) {
    velocity_ += ortho_front();
  }
  if (keys[GLFW_KEY_S]) {
    velocity_ -= ortho_front();
  }
  if (keys[GLFW_KEY_A]) {
    velocity_ -= right();
  }
  if (keys[GLFW_KEY_D]) {
    velocity_ += right();
  }
  if (keys[GLFW_KEY_LEFT_CONTROL]) {
    velocity_ -= up_;
  }
  if (keys[GLFW_KEY_SPACE]) {
    velocity_ += up_;
  }
  velocity_ *= speed;
}
void Camera::UpdatePosition(const float delta_time) {
  position_ += velocity_ * delta_time;
}
void Camera::UpdateCaches(const float delta_time, const bool keys[512]) {
  static const int position_related_keys[6]{
      GLFW_KEY_A,    GLFW_KEY_D, GLFW_KEY_S, GLFW_KEY_W, GLFW_KEY_LEFT_CONTROL,
      GLFW_KEY_SPACE};
  for (const auto i : position_related_keys) {
    should_set_position_ = should_set_position_ || keys[i];
  }
}
float Camera::fov() const { return fov_; }
const glm::vec3 Camera::position() const { return position_; }
const glm::mat4 Camera::view() const {
  return glm::lookAt(position_, position_ + front_, up_);
}
const glm::vec3 Camera::front() const { return front_; }
const glm::vec3 Camera::ortho_front() const {
  return glm::normalize(glm::vec3(front_.x, 0, front_.z));
}
const glm::vec3 Camera::up() const { return up_; }
const glm::vec3 Camera::right() const {
  return glm::normalize(glm::cross(front_, up_));
}
void Camera::add_fov(const float delta) {
  if (fov_ >= 1.0f && fov_ <= 45.0f) fov_ += delta;
  if (fov_ <= 1.0f) fov_ = 1.0f;
  if (fov_ >= 45.0f) fov_ = 45.0f;
}
void Camera::add_pitch(const float delta) {
  pitch_ += delta;
  if (pitch_ > 89.0f) {
    pitch_ = 89.0f;
  }
  if (pitch_ < -89.0f) {
    pitch_ = -89.0f;
  }
}
void Camera::add_yaw(const float delta) { yaw_ += delta; }
bool Camera::direction_changed() const { return should_set_direction_; }
void Camera::set_direction_changed(const bool value) {
  should_set_direction_ = value;
}
