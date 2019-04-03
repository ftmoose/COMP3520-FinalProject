#include "model.h"

Model::Model(const std::string& filePath)
{
	Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    //directory = filePath.substr(0, filePath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}


void Model::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); ++i)
		meshes[i].Draw();
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		glm::vec3 position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec2 texCoords = glm::vec2(0.0f);
		if(mesh->mTextureCoords[0])
			texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		glm::vec3 normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		Vertex vertex(position, texCoords, normal);

		vertices.push_back(vertex);
	}

	// process indices
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}  

	// // process material
	// if (mesh->mMaterialIndex >= 0)
	// {

	// }

	return Mesh(&vertices[0], vertices.size(), &indices[0], indices.size());
}
