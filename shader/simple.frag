#version 330 core
in vec2 texcoord;
in vec3 test;
out vec4 FragColor;
uniform sampler2D simple_sampler;
uniform float c;
void main() {
  FragColor = texture(simple_sampler, texcoord);
}
