#ifndef FIVE_IN_A_ROW_GAME_SHADER_PROGRAM_H
#define FIVE_IN_A_ROW_GAME_SHADER_PROGRAM_H

#include <map>
#include <string>

#include "five_in_a_row_game/fragment_shader.h"
#include "five_in_a_row_game/vertex_shader.h"
#include "glm/fwd.hpp"

class ShaderProgram {
 public:
  ShaderProgram(const VertexShader & vertex_shader,
                const FragmentShader & fragment_shader);
  ShaderProgram(const char * vertex_shader_source,
                const char * fragment_shader_source);
  ShaderProgram(ShaderProgram &&) = delete;
  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram & operator=(ShaderProgram &&) = delete;
  ShaderProgram & operator=(const ShaderProgram &) = delete;
  ~ShaderProgram();

 public:
  void Use() const;
  void Validate() const;
  void SetFloat(const char * name, const float) const;
  void Set3Float(const char * name, const float, const float,
                 const float) const;
  void Set4Float(const char * name, const float, const float, const float,
                 const float) const;
  void SetInt(const char * name, const int &) const;
  void SetVector3(const char * name, const glm::vec3 & vec3) const;
  void SetMatrix4(const char * name, const glm::mat4 & mat4) const;
  void SetTransposedMatrix4(const char * name, const glm::mat4 & mat4) const;

  unsigned id() const { return id_; }

 private:
  int GetUniformLocation(const char * name) const;
  int GetInfoLogLength() const;
  void CheckErrors() const;

 private:
  static unsigned being_used_shader_program_id_;
  // Since every shader has different uniform locations, we don't set this to be
  // static.
  mutable std::map<std::string, int> name_uniform_location_map_;
  unsigned id_;
};

#endif  // FIVE_IN_A_ROW_GAME_SHADER_PROGRAM_H
