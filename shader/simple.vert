#version 330 core
layout (location = 0) in vec2 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;
out vec2 texcoord;
out vec2 frag_position;
uniform mat4 model;
uniform mat4 projection;
void main() {
  texcoord = vertex_texcoord;
  gl_Position = model * vec4(vertex_position, 0, 1);
  frag_position = (projection * gl_Position).xy;
}
