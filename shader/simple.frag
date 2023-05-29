#version 330 core
in vec2 texcoord;
out vec4 frag_color;
uniform sampler2D simple_sampler;
uniform float c;
void main() {
  frag_color = texture(simple_sampler, texcoord);
}
