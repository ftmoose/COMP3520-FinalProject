#include <iostream>
#include "display.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"
#include "transform.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

void DrawBezierSurface(const GLfloat *points);

int main()
{

	Display display(800, 600, "project2");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), 	glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), 	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), 	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), 	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),

		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), 	glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), 	glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), 	glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), 	glm::vec2(0.0f, 1.0f)),
	};

	unsigned int indices[] = { 
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	};

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	
	Model awp("../models/csgo-awp/Model.obj");
	Model city3("../models/city3/Organodron City/Organodron City.obj");
	Model cat("../models/cat/cat.obj");
	Shader shader("../shaders/shader");
	Shader shader2("../shaders/shader");
	Shader lightShader("../shaders/lightShader");

	int width, height;
	glfwGetWindowSize(display.GetWindow(), &width, &height);
	Camera camera(glm::vec3(0, 0, -5.0f), 45.0f, (float)width/height, 0.1f, 1000.0f, display.GetWindow()); 

	Transform transform;
	Transform transform2;

	glm::vec3 lightPos0 = glm::vec3(0, -30, 0);

	float dir = 1;

	while (!display.IsClosed())
	{
		display.ProcessInput();
		camera.ProcessInput(display.GetWindow());
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();

		display.DisableCullFace();

			lightShader.Bind();

			transform.SetPos(lightPos0);
			transform.SetRot(glm::vec3(0, 0, 0));
			lightShader.Update(transform, camera);

			mesh.Draw(lightShader);

		display.EnableCullFace();

		shader.Bind();
		shader.setVec3("lightPos0", lightPos0);
		shader.setVec3("viewPos0", camera.GetPosition());

		float time = glfwGetTime();

		transform.SetRot(glm::vec3(0, 0, 0));
		transform.SetPos(glm::vec3(0, 0, -20));
		city3.Draw(shader);
		shader.Update(transform, camera);

		shader2.Bind();

		transform2.SetPos(glm::vec3(cos(time) * 100, 0, 0));
		transform2.SetRot(glm::vec3(0, cos(time) * 50 - 90, 0));

		cat.Draw(shader2);
		shader2.Update(transform2, camera);

		// transform.SetPos(glm::vec3(0, 40, -20));
		// city.Draw(shader);

		// transform.SetPos(glm::vec3(0, -40, -20));
		// planets[1].Draw(shader);
		// shader.Update(transform, camera);

		display.Update();
	} 

	return 0;
}