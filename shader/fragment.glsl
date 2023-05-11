#version 330 core

in vec3 frag_pos;
in vec3 normal;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 light_position;

void main() {
  vec3 lightColor = vec3(0.5f);
  vec3 light_direction = normalize(frag_pos - light_position);

  float ambient_ratio = 0.1f;
  vec3 ambient = ambient_ratio * lightColor;

  float diffuse_ratio = max(dot(-light_direction, normal), 0.0f);
  vec3 diffuse = diffuse_ratio * lightColor;

  vec4 object_color = texture(tex0, texcoord);
  FragColor = vec4((ambient+diffuse) * object_color.xyz, object_color.w);
}
