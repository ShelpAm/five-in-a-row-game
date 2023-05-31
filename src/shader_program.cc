#include "five_in_a_row_game/shader_program.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include "five_in_a_row_game/fragment_shader.h"
#include "five_in_a_row_game/shader_errors.h"
#include "five_in_a_row_game/texture2d.h"
#include "five_in_a_row_game/vertex_shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(const VertexShader & vertex_shader,
                             const FragmentShader & fragment_shader)
    : id_(glCreateProgram()) {
  vertex_shader.AttachTo(*this);
  fragment_shader.AttachTo(*this);
  glLinkProgram(id_);
  CheckErrors();
  vertex_shader.DetachFrom(*this);
  fragment_shader.DetachFrom(*this);
}

ShaderProgram::ShaderProgram(const char * vertex_shader_source,
                             const char * fragment_shader_source)
    : ShaderProgram(VertexShader(vertex_shader_source),
                    FragmentShader(fragment_shader_source)) {}

ShaderProgram::~ShaderProgram() { glDeleteProgram(id_); }

void ShaderProgram::Use() const {
  if (being_used_shader_program_id_ != id_) {
    glUseProgram(id_);
    being_used_shader_program_id_ = id_;
  }
#ifdef DEBUG
  Validate();
#endif  // !DEBUG
}

void ShaderProgram::SetFloat(const char * name, const float value) const {
  Use();
  glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::Set3Float(const char * name, const float value1,
                              const float value2, const float value3) const {
  Use();
  glUniform3f(GetUniformLocation(name), value1, value2, value3);
}

void ShaderProgram::Set4Float(const char * name, const float value1,
                              const float value2, const float value3,
                              const float value4) const {
  Use();
  glUniform4f(GetUniformLocation(name), value1, value2, value3, value4);
}

void ShaderProgram::SetInt(const char * name, const int & value1) const {
  Use();
  // FIXME
  // glProgramUniform1iv(id_, GetUniformLocation(name), 1, &value1);
  glUniform1iv(GetUniformLocation(name), 1, &value1);
}

void ShaderProgram::SetVector3(const char * name,
                               const glm::vec3 & vec3) const {
  Use();
  glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec3));
}

void ShaderProgram::SetMatrix4(const char * name,
                               const glm::mat4 & mat4) const {
  Use();
  glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(mat4));
}

void ShaderProgram::SetTransposedMatrix4(const char * name,
                                         const glm::mat4 & mat4) const {
  Use();
  glUniformMatrix4fv(GetUniformLocation(name), 1, true, glm::value_ptr(mat4));
}

void ShaderProgram::BindTexture(const Texture2D & texture, const char * name,
                                const int & slot) const {
  texture.Bind(*this, name, slot);
}

void ShaderProgram::Validate() const {
  glValidateProgram(id_);
  int successful;
  glGetProgramiv(id_, GL_VALIDATE_STATUS, &successful);
  if (!successful) {
    int info_log_length = GetInfoLogLength();
    std::vector<char> info_log(info_log_length);
    glGetProgramInfoLog(id_, info_log_length, NULL, &(info_log[0]));
    std::cout << "ERROR::SHADER::PROGRAM::ValidateFailed ";
    std::cerr << &(info_log[0]) << std::endl;
    throw ShaderCompilationError();
  }
}

int ShaderProgram::GetUniformLocation(const char * name) const {
  if (name_uniform_location_map_.contains(name)) {
    return name_uniform_location_map_.at(name);
  } else {
    const auto uniform_location = glGetUniformLocation(id_, name);
    name_uniform_location_map_[name] = uniform_location;
    return uniform_location;
  }
}

int ShaderProgram::GetInfoLogLength() const {
  int length;
  glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);
  return length;
}

void ShaderProgram::CheckErrors() const {
  int successful;
  glGetProgramiv(id_, GL_LINK_STATUS, &successful);
  if (!successful) {
    auto length = GetInfoLogLength();
    std::vector<char> info_log(length);
    glGetProgramInfoLog(id_, length, NULL, &(info_log[0]));
    std::cerr << "Error::ShaderProgram::LinkFailed " << &(info_log[0]) << "\n";
    throw ShaderCompilationError();
  }
}

unsigned ShaderProgram::being_used_shader_program_id_(-1);
