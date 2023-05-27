#version 330 core
in vec2 texcoord;
in vec2 frag_position;
out vec4 frag_color;
uniform sampler2D simple_sampler;
uniform float c;
void main() {
  // frag_color = texture(simple_sampler, texcoord);
  frag_color.xy = frag_position * c + c;
  frag_color.z = 0;
  frag_color.w = 1;
}
