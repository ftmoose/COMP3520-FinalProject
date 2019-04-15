#include "mesh.h"

#include <iostream>
#include <vector>
#include <iostream>

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, std::vector<Texture> ts)
{
	textures = ts;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	for (unsigned int i = 0; i < numVertices; ++i)
	{
		positions.push_back(vertices[i].GetPos());
		texCoords.push_back(vertices[i].GetTexCoord());
		normals.push_back(vertices[i].GetNormal());
	}

	drawCount = numIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(NUM_BUFFERS, VBO);

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// texCoords
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, normals.size()  * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	for (unsigned int i = 0; i < numVertices; ++i)
	{
		positions.push_back(vertices[i].GetPos());
		texCoords.push_back(vertices[i].GetTexCoord());
		normals.push_back(vertices[i].GetNormal());
	}

	drawCount = numIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(NUM_BUFFERS, VBO);

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// texCoords
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, normals.size()  * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

// Mesh::~Mesh()
// {
// 	glDeleteVertexArrays(1, &VAO);
// }

void Mesh::Draw(Shader& shader)
{
	shader.Bind();
	unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].GetType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].GetTex());
    }
    glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}