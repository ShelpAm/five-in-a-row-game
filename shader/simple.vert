#version 330 core
layout (location = 0) in vec2 vert_pos;
layout (location = 1) in vec2 vert_texcoord;
out vec2 texcoord;
uniform mat4 model;
uniform mat4 projection;
void main() {
  texcoord = vert_texcoord;
  gl_Position = /*projection **/ model * vec4(vert_pos, 0, 1);
  }
