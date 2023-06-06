#ifndef FIVE_IN_A_ROW_GAME_TEXTURE2D_H
#define FIVE_IN_A_ROW_GAME_TEXTURE2D_H

#include <string>

#include "five_in_a_row_game/application_fwd.h"
#include "five_in_a_row_game/shader_program_fwd.h"
#include "five_in_a_row_game/window.h"
#include "glm/glm.hpp"

class Texture2D {
 public:
  Texture2D() = delete;
  explicit Texture2D(const char * file_name);
  Texture2D(Texture2D &&) = default;
  Texture2D(const Texture2D &) = delete;
  Texture2D & operator=(Texture2D &&) = delete;
  Texture2D & operator=(const Texture2D &) = delete;
  ~Texture2D();

  /// @brief Generates a texture from the `file_name_`.
  /// Before using the texture, we should first call this function.
  void Generate();

  void Destroy();

  /// @brief Binds the texture to a binging point on a certain shader program.
  /// @param[in] shader_program The shader program you want to use.
  /// @param[in] name The name of sampler to bind to.
  /// @param[in] which The binding point to be bound to.
  void Bind(const ShaderProgram & shader_program, const char * name,
            const unsigned which) const;

  void Render(const ShaderProgram & shader_program, const Window & window,
              const glm::vec3 & position, const float rotation,
              const glm::vec3 & scale, const glm::vec3 & color) const;

 private:
  std::string file_name_;
  unsigned id_;
  mutable bool generated_ = false;
};

#endif  // FIVE_IN_A_ROW_GAME_TEXTURE2D_H
