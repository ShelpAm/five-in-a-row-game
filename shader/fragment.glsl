#version 330 core

in vec3 frag_pos;
in vec3 light_pos;
in vec3 normal;
in vec2 texcoord;

out vec4 FragColor;

struct Material {
  sampler2D diffuse_map;
  sampler2D specular_map;
  float shininess;
};

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct DirectionalLight {
  Light light;
  vec3 direction;
};

struct PointLight {
  Light light;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

uniform sampler2D tex;

uniform vec3 camera_pos;
uniform Material material;
uniform DirectionalLight dir_light;
uniform PointLight point_light;

vec3 ambient(Material material, Light light) {
  return texture(material.diffuse_map, texcoord).xyz * light.ambient;
}

vec3 diffuse(Material material, Light light, vec3 light_dir) {
  return max(dot(-light_dir, normal), 0) * texture(material.diffuse_map, texcoord).xyz * light.diffuse;
}

vec3 specular(Material material, Light light, vec3 viewer_dir, vec3 light_dir) {
  return pow(max(dot(viewer_dir, reflect(light_dir, normal)), 0), material.shininess) * texture(material.specular_map, texcoord).xyz * light.specular;
}

vec4 CalculateDirectionalLight(DirectionalLight dir_light) {
  vec3 light_dir = normalize(dir_light.direction);
  vec3 viewer_dir = normalize(camera_pos - frag_pos);

  vec3 result = vec3(0);
  result += ambient(material, dir_light.light);
  result += diffuse(material, dir_light.light, light_dir);
  result += specular(material, dir_light.light, viewer_dir, light_dir);
  return vec4(result, 1.0f);
}

vec4 CalculatePointLight(PointLight point_light) {
  vec3 light_dir = normalize(frag_pos - point_light.position);
  vec3 viewer_dir = normalize(camera_pos - frag_pos);

  vec3 result = vec3(0);
  result += ambient(material, point_light.light);
  result += diffuse(material, point_light.light, light_dir);
  result += specular(material, point_light.light, viewer_dir, light_dir);

  float distance    = length(point_light.position - frag_pos);
  float attenuation = 1.0f / (point_light.constant + point_light.linear * distance + point_light.quadratic * pow(distance, 2));
  result *= attenuation;
  return vec4(result, 1.0f);
}

void main() {
  FragColor = vec4(0.0f);
  FragColor += CalculateDirectionalLight(dir_light);
  FragColor += CalculatePointLight(point_light);
}
