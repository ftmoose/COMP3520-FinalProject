#include <iostream>
#include "display.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "transform.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

int main() 
{

	Display display(800, 600, "project2");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
	};

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(unsigned int));
	Mesh mesh2("./models/monkey.obj");
	Shader shader("./shaders/shader");
	Texture texture("./textures/wall.jpg");

	int width, height;
	glfwGetWindowSize(display.GetWindow(), &width, &height);
	Camera camera(glm::vec3(0, 0, -10.0f), 45.0f, (float)width/height, 0.1f, 100.0f); 

	Transform transform;

	while (!display.IsClosed())
	{
		display.ProcessInput();
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		shader.Bind();
		texture.Bind(0);

		float time = glfwGetTime();
		transform.SetRot(glm::vec3(time*50, time*50, 0));
		transform.SetScale(glm::vec3(cos(time)+2,cos(time)+2,cos(time)+2));

		shader.Update(transform, camera);
		mesh2.Draw();

		display.Update();
	} 

	return 0;
}