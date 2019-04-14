#version 330 core

out vec4 FragColor;
uniform sampler2D texture0;
in vec2 texCoord0;
in vec3 normal0;
in vec3 position0;

uniform vec3 lightPos0;
uniform vec3 viewPos0;

void main() {

	float ambientStrength = 0.1;
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(lightPos0 - position0);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos0 - position0);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;



	FragColor = vec4(ambient + diffuse + specular, 1.0) * texture(texture0, texCoord0);
}