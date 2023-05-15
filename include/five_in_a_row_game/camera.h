#ifndef FIVE_IN_A_ROW_GAME_CAMERA_H_
#define FIVE_IN_A_ROW_GAME_CAMERA_H_

#include "five_in_a_row_game/shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class Camera {
 public:
  Camera();
  Camera(const glm::vec3 & pos, const float fov, const float pitch,
         const float yaw);
  void Update(const float delta_time, const bool keys[256]);
  float fov() const { return fov_; }
  const glm::vec3 position() const { return position_; }
  const glm::mat4 look_at() const {
    return glm::lookAt(position_, position_ + front_, up_);
  }
  const glm::vec3 front() const { return front_; }
  const glm::vec3 up() const { return up_; }
  const glm::vec3 right() const {
    return glm::normalize(glm::cross(front_, up_));
  }
  void add_fov(const float delta) {
    if (fov_ >= 1.0f && fov_ <= 45.0f) fov_ += delta;
    if (fov_ <= 1.0f) fov_ = 1.0f;
    if (fov_ >= 45.0f) fov_ = 45.0f;
  }
  void add_pitch(const float delta) {
    pitch_ += delta;
    if (pitch_ > 89.0f) {
      pitch_ = 89.0f;
    }
    if (pitch_ < -89.0f) {
      pitch_ = -89.0f;
    }
  }
  void add_yaw(const float delta) { yaw_ += delta; }

 private:
  float fov_{45.0f};
  float yaw_{-90}, pitch_{0};
  glm::vec3 position_{0.0f, 0.0f, 15.0f};
  glm::vec3 front_{0.0f, 0.0f, -1.0f}, up_{0.0f, 1.0f, 0.0f};
  glm::vec3 velocity_{};
};

#endif  // FIVE_IN_A_ROW_GAME_CAMERA_H_