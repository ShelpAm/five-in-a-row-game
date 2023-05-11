#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal_;
layout (location = 2) in vec2 texcoord_;

out vec3 frag_pos;
out vec3 normal;
out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  frag_pos = vec3(model * vec4(pos, 1.0f));
  /* 矩阵求逆是一项对于着色器开销很大的运算，因为它必须在场景中的每一个顶点上进行，
   所以应该尽可能地避免在着色器中进行求逆运算。以学习为目的的话这样做还好，
   但是对于一个高效的应用来说，你最好先在CPU上计算出法线矩阵，再通过uniform
   把它传递给着色器（就像模型矩阵一样）。 */
  normal = mat3(transpose(inverse(model))) * normal_;
  texcoord = texcoord_;
}

