#ifndef MESH_H
#define MESH_H

#include "obj_loader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0)) 
	{ 
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3 GetPos() { return pos; }
	inline glm::vec2 GetTexCoord() { return texCoord; }
	inline glm::vec3 GetNormal() { return normal; }

  private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal; 
};

class Mesh
{
public:
	std::vector<Texture> textures;

	Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, std::vector<Texture> textures);

	void Draw(Shader& shader);

private:

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint VAO;
	GLuint VBO[NUM_BUFFERS];
	unsigned int drawCount;
};

#endif