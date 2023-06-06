#version 330 core

struct Material {
  sampler2D diffuse_sampler;
  sampler2D specular_sampler;
  float shininess;
};

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct Attenuation {
  float constant;
  float linear;
  float quadratic;
};

struct DirectionalLight {
  Light light;
  vec3 direction;
};

struct PointLight {
  Light light;
  vec3 position;
  Attenuation attenuation;
};

struct SpotLight {
  Light light;
  vec3 position;
  vec3 direction;
  float cos_phi;
  float cos_gamma;
  Attenuation attenuation;
};

in vec3 frag_pos;
in vec3 normal;
in vec2 texcoord;

out vec4 frag_color;

uniform vec3 camera_pos;
uniform Material material;
uniform DirectionalLight dir_light;
#define kNumPointLight 1
uniform PointLight point_lights[kNumPointLight];
uniform SpotLight spot_light;

vec3 ambient(Material material, Light light);
vec3 diffuse(Material material, Light light, vec3 light_dir);
vec3 specular(Material material, Light light, vec3 viewer_dir, vec3 light_dir);
vec4 CalculateDirectionalLight(DirectionalLight dir_light);
vec4 CalculatePointLight(PointLight point_light);
vec4 CalculateSpotLight(SpotLight spot_light);
float attenuation(float distance, Attenuation attenuation);

vec3 ambient(Material material, Light light) {
  return texture(material.diffuse_sampler, texcoord).xyz * light.ambient;
}

vec3 diffuse(Material material, Light light, vec3 light_dir) {
  return max(dot(-light_dir, normal), 0) * texture(material.diffuse_sampler, texcoord).xyz * light.diffuse;
}

vec3 specular(Material material, Light light, vec3 viewer_dir, vec3 light_dir) {
  return pow(max(dot(viewer_dir, reflect(light_dir, normal)), 0), material.shininess) * texture(material.specular_sampler, texcoord).xyz * light.specular;
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
  result *= attenuation(distance(point_light.position, frag_pos), point_light.attenuation);
  return vec4(result, 1.0f);
}

vec4 CalculateSpotLight(SpotLight spot_light) {
  vec3 light_dir = normalize(spot_light.direction);
  vec3 viewer_dir = normalize(camera_pos - frag_pos);
  vec3 result = vec3(0);
  float cos_theta = dot(light_dir, normalize(frag_pos - spot_light.position));
  float epsilon = spot_light.cos_phi - spot_light.cos_gamma;
  float intensity = clamp((cos_theta - spot_light.cos_gamma) / epsilon, 0.0f, 1.0f);
  result += ambient(material, spot_light.light);
  result += diffuse(material, spot_light.light, light_dir);
  result += specular(material, spot_light.light, viewer_dir, light_dir);
  result *= intensity;
  result *= attenuation(distance(spot_light.position, frag_pos), spot_light.attenuation);
  return vec4(result, 1.0f);
}

float attenuation(float distance, Attenuation attenuation) {
  return 1.0f / (attenuation.constant + attenuation.linear * distance + attenuation.quadratic * pow(distance, 2));
}

void main() {
  frag_color = vec4(0.0f);
  frag_color += CalculateDirectionalLight(dir_light);
  for (int i = 0; i!= kNumPointLight; i++) {
    frag_color += CalculatePointLight(point_lights[i]);
  }
  frag_color += CalculateSpotLight(spot_light);
  frag_color.w = texture(material.diffuse_sampler, texcoord).w;
}
