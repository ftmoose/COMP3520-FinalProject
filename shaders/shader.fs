#version 330 core

out vec4 FragColor;
uniform sampler2D diffuse;
in vec2 texCoord0;
in vec3 normal0;

void main() {
	FragColor = 	texture(diffuse, texCoord0)
					* clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0);
}