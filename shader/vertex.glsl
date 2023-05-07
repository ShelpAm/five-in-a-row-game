#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 frag_color_;
layout (location = 2) in vec2 texcoord_;
// out vec3 frag_color;
out vec2 texcoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
   gl_Position = projection * view * model * vec4(pos, 1.0f);
   // frag_color = frag_color_;
   texcoord = texcoord_;
}

