#include "five_in_a_row_game/shader.h"

#include <cstddef>
#include <iostream>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const char * vertex_shader_source,
               const char * fragment_shader_source) {
  unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

  glCompileShader(vertex_shader);
  CheckShaderErrors(vertex_shader);
  glCompileShader(fragment_shader);
  CheckShaderErrors(fragment_shader);

  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertex_shader);
  glAttachShader(shader_program_, fragment_shader);
  glLinkProgram(shader_program_);
  CheckShaderProgramErrors();

  glDetachShader(shader_program_, vertex_shader);
  glDetachShader(shader_program_, fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader() {
  Use();
  glDeleteProgram(shader_program_);
}

void Shader::Use() const { glUseProgram(shader_program_); }

void Shader::Uniform4f(const char * name, const float value1,
                       const float value2, const float value3,
                       const float value4) const {
  Use();
  glUniform4f(GetUniformLocation(name), value1, value2, value3, value4);
}

void Shader::Uniform1i(const char * name, const int value1) const {
  Use();
  glUniform1i(GetUniformLocation(name), value1);
}

void Shader::UniformMatrix4fv(const char * name, const glm::mat4 & mat4) const {
  Use();
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(mat4));
}

int Shader::GetUniformLocation(const char * name) const {
  const auto uniform_location = glGetUniformLocation(shader_program_, name);
  return uniform_location;
}

void Shader::CheckShaderErrors(const unsigned shader) const {
  static std::size_t times{0};
  const char * shader_name;
  if (times % 2 == 0) {
    shader_name = "VERTEX";
  } else {
    shader_name = "FRAGMENT";
  }
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::" << shader_name << "::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  times++;
}

void Shader::CheckShaderProgramErrors() const {
  int success;
  char infoLog[512];
  glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
}
