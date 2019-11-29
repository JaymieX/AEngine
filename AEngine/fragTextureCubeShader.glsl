#version 410 core
out vec4 fragColor;

in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 fragPosition;

uniform sampler2D inputTexture;
uniform vec3 cameraPos;
uniform struct Light 
{
	vec3 position;
	float ambient;
	float diffuse;
	vec3 color;
} light;

void main() 
{
	vec3 ambient = light.ambient * texture(inputTexture, vertexUV).rgb * light.color;

	vec3 n = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(n, lightDir), 0.0);
	vec3 diffuse = diff * texture(inputTexture, vertexUV).rgb * light.color;

	vec3 viewDir = normalize(cameraPos - fragPosition);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = 0.5 * spec * light.color;

	fragColor = vec4(ambient + diffuse + specular, 1.0f);
}