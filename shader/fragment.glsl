#version 330 core
// in vec3 frag_color;
in vec2 texcoord;
out vec4 FragColor;
uniform sampler2D tex0;
uniform sampler2D tex1;
void main() {
  FragColor = texture(tex0, texcoord);
}
