#include "five_in_a_row_game/texture2d.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/window.h"
#include "glad/gl.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb/stb_image.h"

Texture2D::Texture2D(const char * file_name) : file_name_(file_name) {
  Generate();
}

Texture2D::~Texture2D() {}

void Texture2D::Generate() {
  if (generated_) {
    return;
  }
  int width, height, num_of_channels;
  unsigned char * data =
      stbi_load(file_name_.c_str(), &width, &height, &num_of_channels, 0);
  if (!data) {
    throw std::runtime_error("Texture2D::STB failed to load image.");
  }
  unsigned format = GL_RGBA - 4 + num_of_channels;
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  generated_ = true;
}

void Texture2D::Bind(const ShaderProgram & shader_program, const char * name,
                     const unsigned which) const {
  shader_program.Use();
  shader_program.SetInt(name, which);
  glActiveTexture(GL_TEXTURE0 + which);
  glBindTexture(GL_TEXTURE_2D, id_);
  // FIXME On Windows platform this doesn't work.
  // glBindTextureUnit(which, id_);
}

void Texture2D::Render(const ShaderProgram & shader_program,
                       const Window & window, const glm::vec3 & position,
                       const float rotation, const glm::vec3 & scale,
                       const glm::vec3 & color) const {
  const float width = window.width();
  const float height = window.height();
  constexpr float z_near = -1.0f;
  constexpr float z_far = 1.0f;
  glm::mat4 model(1.0f);
  model = glm::translate(model, position);
  model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, scale);
  glm::mat4 projection =
      glm::ortho(0.0f, width / 200, height / 150, 0.0f, z_near, z_far);
  // projection = glm::mat4(1.0f);

  shader_program.Use();
  shader_program.SetMatrix4("model", model);
  shader_program.SetMatrix4("projection", projection);
  shader_program.BindTexture(*this, "simple_sampler", 0);
  constexpr float vertices[][2][2]{
      {{0, 0}, {0, 1}}, {{1, 0}, {1, 1}}, {{0, 1}, {0, 0}}, {{1, 1}, {1, 0}}};
  constexpr int indices[]{0, 1, 2, 1, 2, 3};
  glm::vec4 v1[4];
  for (size_t i = 0; i < 4; i++) {
    glm::vec4 v(vertices[i][0][0], vertices[i][0][1], 0, 1);
    v1[i] = projection * model * v;
  }
  unsigned vao;
  unsigned vbo;
  unsigned ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)(2 * sizeof(float)));

  // glBindVertexArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDisable(GL_DEPTH_TEST);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  window.UpdateDepthTestState();

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}
void Texture2D::Destroy() { glDeleteTextures(1, &id_); }
