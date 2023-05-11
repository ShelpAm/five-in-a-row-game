#ifndef FIVE_IN_A_ROW_GAME_SHADER_H_
#define FIVE_IN_A_ROW_GAME_SHADER_H_

#include "glm/fwd.hpp"
class Shader {
 public:
  Shader(const char * vertex_shader_source,
         const char * fragment_shader_source);
  ~Shader();
  void Use() const;
  void Uniform3f(const char * name, const float, const float,
                 const float) const;
  void Uniform4f(const char * name, const float, const float, const float,
                 const float) const;
  void Uniform1i(const char * name, const int) const;
  void UniformMatrix4fv(const char * name, const glm::mat4 & mat4) const;

 private:
  friend class Application;
  int GetUniformLocation(const char * name) const;
  void CheckShaderErrors(const unsigned shader) const;
  void CheckShaderProgramErrors() const;

 private:
  unsigned shader_program_{};
};

#endif  // FIVE_IN_A_ROW_GAME_SHADER_H_
