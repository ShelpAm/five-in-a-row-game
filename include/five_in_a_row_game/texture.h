#ifndef FIVE_IN_A_ROW_GAME_TEXTURE_H
#define FIVE_IN_A_ROW_GAME_TEXTURE_H

#include "five_in_a_row_game/application_fwd.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/window.h"

class Texture2D {
 public:
  Texture2D(const char * file_name);
  ~Texture2D();
  void Bind(const ShaderProgram & shader_program, const unsigned which) const;
  void Render(const ShaderProgram & shader_program, const glm::vec3 & position,
              const glm::vec3 & size, const glm::vec3 & color) const;

 private:
  unsigned id_;
};

#endif  // FIVE_IN_A_ROW_GAME_TEXTURE_H
