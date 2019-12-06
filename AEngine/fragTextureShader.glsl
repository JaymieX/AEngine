#version 410 core
out vec4 fragColor;

in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 fragPosition;

uniform vec3 cameraPos;
uniform struct Light 
{
	vec3 position;
	float ambient;
	float diffuse;
	vec3 color;
} light;
uniform struct Material
{
	sampler2D diffuseMap;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float roughness; 
	float specular;
	float transparency;
} material;

void main() 
{
	vec3 ambient = light.ambient * material.ambientColor * texture(material.diffuseMap, vertexUV).rgb * light.color;

	vec3 n = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(n, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuseColor) * texture(material.diffuseMap, vertexUV).rgb * light.color;

	vec3 viewDir = normalize(cameraPos - fragPosition);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.roughness);
	vec3 specular = (spec * material.specular) * light.color;

	fragColor = vec4(ambient + diffuse + specular, material.transparency);
}