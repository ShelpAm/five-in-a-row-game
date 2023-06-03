#include "five_in_a_row_game/fragment_shader.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include "five_in_a_row_game/main.h"
#include "five_in_a_row_game/shader_errors.h"
#include "five_in_a_row_game/shader_program.h"
#include "glad/gl.h"

FragmentShader::FragmentShader(const char * source)
    : id_(glCreateShader(GL_FRAGMENT_SHADER)) {
  glShaderSource(id_, 1, &source, NULL);
  glCompileShader(id_);
  CheckErrors();
}

FragmentShader::FragmentShader(int _placeholder, const char * filename)
    : FragmentShader(GetFileContents(filename).c_str()) {}

FragmentShader::~FragmentShader() { glDeleteShader(id_); }

void FragmentShader::AttachTo(const ShaderProgram & shader_program) const {
  glAttachShader(shader_program.id(), id_);
}

void FragmentShader::DetachFrom(const ShaderProgram & shader_program) const {
  glDetachShader(shader_program.id(), id_);
}

void FragmentShader::CheckErrors() const {
  int length;
  glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);
  int success;
  std::vector<char> info_log(length);
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id_, length, NULL, &(info_log[0]));
    std::cerr << &(info_log[0]) << std::endl;
    throw ShaderCompilationError();
  }
}
