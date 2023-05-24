#include "five_in_a_row_game/shader_program.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include "five_in_a_row_game/fragment_shader.h"
#include "five_in_a_row_game/shader_errors.h"
#include "five_in_a_row_game/vertex_shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(const VertexShader & vertex_shader,
                             const FragmentShader & fragment_shader)
    : id_(glCreateProgram()) {
  vertex_shader.AttachTo(*this);
  fragment_shader.AttachTo(*this);
  glLinkProgram(id_);
  vertex_shader.DetachFrom(*this);
  fragment_shader.DetachFrom(*this);
  CheckErrors();
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
  glProgramUniform1iv(id_, GetUniformLocation(name), 1, &value1);
}

void ShaderProgram::SetVector3(const char * name, const glm::vec3 & vec3) {
  Use();
  glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec3));
}

void ShaderProgram::SetMatrix4(const char * name,
                               const glm::mat4 & mat4) const {
  Use();
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(mat4));
}

void ShaderProgram::Validate() const {
  glValidateProgram(id_);
  int success;
  glGetProgramiv(id_, GL_VALIDATE_STATUS, &success);
  if (!success) {
    int length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);
    std::vector<char> info_log(length);
    glGetProgramInfoLog(id_, length, NULL, &(info_log[0]));
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    std::cerr << &(info_log[0]) << std::endl;
    throw ShaderCompilationError();
  }
}

int ShaderProgram::GetUniformLocation(const char * name) const {
  const auto uniform_location = glGetUniformLocation(id_, name);
  return uniform_location;
}

void ShaderProgram::CheckErrors() const {
  int success;
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (!success) {
    int length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);
    std::vector<char> info_log(length);
    glGetProgramInfoLog(id_, length, NULL, &(info_log[0]));
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    std::cerr << &(info_log[0]) << std::endl;
    throw ShaderCompilationError();
  }
}

unsigned ShaderProgram::being_used_shader_program_id_(-1);
