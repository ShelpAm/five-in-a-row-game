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

struct DirectionalLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


uniform Material material;
uniform DirectionalLight directional_light;
uniform PointLight point_light;

void main() {
  vec3 light_dir = normalize(frag_pos - light_pos);
  vec3 viewer_dir = normalize(-frag_pos);

  vec3 ambient = texture(material.diffuse_map, texcoord).xyz * directional_light.ambient;

  float diffuse_ratio = max(dot(-directional_light.direction, normal), 0.0f);
  vec3 diffuse = diffuse_ratio * texture(material.diffuse_map, texcoord).xyz * directional_light.diffuse;

  float specular_ratio = pow(max(dot(viewer_dir, reflect(directional_light.direction, normal)), 0.0), material.shininess);
  vec3 specular = specular_ratio * texture(material.specular_map, texcoord).xyz * directional_light.specular;

  FragColor = vec4((ambient + diffuse + specular), 1.0f) ;
}
