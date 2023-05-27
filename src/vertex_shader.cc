#include "five_in_a_row_game/vertex_shader.h"

#include <cstddef>
#include <iostream>
#include <vector>

#include "five_in_a_row_game/main.h"
#include "five_in_a_row_game/shader_errors.h"
#include "five_in_a_row_game/shader_program.h"
#include "glad/glad.h"

VertexShader::VertexShader(const char * source)
    : id_(glCreateShader(GL_VERTEX_SHADER)) {
  glShaderSource(id_, 1, &source, NULL);
  glCompileShader(id_);
  CheckErrors();
}

VertexShader::VertexShader(int _placeholder, const char * filename)
    : VertexShader(GetFileContents(filename).c_str()) {}

VertexShader::~VertexShader() { glDeleteShader(id_); }

void VertexShader::AttachTo(const ShaderProgram & shader_program) const {
  glAttachShader(shader_program.id(), id_);
}

void VertexShader::DetachFrom(const ShaderProgram & shader_program) const {
  glDetachShader(shader_program.id(), id_);
}

void VertexShader::CheckErrors() const {
  int successful;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &successful);
  if (!successful) {
    int length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);
    std::vector<char> info_log(length);
    glGetShaderInfoLog(id_, length, NULL, &(info_log[0]));
    std::cerr << &(info_log[0]) << std::endl;
    throw ShaderCompilationError();
  }
}
