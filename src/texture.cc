#include "five_in_a_row_game/texture.h"

#include <iostream>

#include "glad/glad.h"
#include "stb/stb_image.h"

Texture2D::Texture2D(const char * file_name) {
  int width, height, num_channels;
  unsigned char * data =
      stbi_load(file_name, &width, &height, &num_channels, 0);
  if (!data) {
    std::cout << "ERROR::Texture2D::STB::LOAD failed to load image\n";
    return;
  }
  unsigned format = GL_RGBA - 4 + num_channels;
  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_2D, texture_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
}

void Texture2D::Bind(const unsigned which) const {
  glActiveTexture(GL_TEXTURE0 + which);
  glBindTexture(GL_TEXTURE_2D, texture_id_);
}
