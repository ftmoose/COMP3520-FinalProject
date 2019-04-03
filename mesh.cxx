#include "mesh.h"

#include <iostream>
#include <vector>
#include <iostream>

Mesh::Mesh(const std::string& filePath)
{
	IndexedModel model = OBJModel(filePath).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; ++i) {
		model.positions.push_back(vertices[i].GetPos());
		model.texCoords.push_back(vertices[i].GetTexCoord());
		model.normals.push_back(vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; ++i)
		model.indices.push_back(indices[i]);

	InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	drawCount = model.indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(NUM_BUFFERS, VBO);

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// texCoords
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size()  * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);

	//glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}