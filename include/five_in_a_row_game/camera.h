#ifndef FIVE_IN_A_ROW_GAME_CAMERA_H_
#define FIVE_IN_A_ROW_GAME_CAMERA_H_

#include "five_in_a_row_game/window.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "shader_program.h"

class Camera {
 public:
  Camera();
  Camera(const glm::vec3 & pos, const float fov, const float pitch,
         const float yaw);
  void Update(const float delta_time, const bool keys[512]);
  void UpdateDirections(const float delta_time);
  void UpdatePosition(const float delta_time);
  void UpdateVelocity(const float delta_time, const bool keys[512]);
  void UpdateCaches(const float delta_time, const bool keys[512]);

  /// @brief Sets uniforms.
  /// This method receives a window object because the uniform variables should
  /// be set depending on the window.
  void SetUniforms(const ShaderProgram & shader_program, const Window &);
  float fov() const;
  const glm::vec3 position() const;
  const glm::mat4 view() const;
  const glm::vec3 front() const;
  // FIXME: alter to a formal name.
  const glm::vec3 ortho_front() const;
  const glm::vec3 up() const;
  const glm::vec3 right() const;
  void add_fov(const float delta);
  void add_pitch(const float delta);
  void add_yaw(const float delta);
  bool direction_changed() const;
  void set_direction_changed(const bool value);

 private:
  float fov_{45.0f};
  float yaw_{-90}, pitch_{0};
  glm::vec3 position_{0.0f, 0.0f, 5.0f};
  glm::vec3 front_{0.0f, 0.0f, -1.0f};
  glm::vec3 up_{0.0f, 1.0f, 0.0f};
  glm::vec3 velocity_{};
  bool should_set_position_ = true;
  bool should_set_direction_ = true;
};

#endif  // FIVE_IN_A_ROW_GAME_CAMERA_H_
