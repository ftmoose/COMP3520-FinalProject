#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	std::string directory;

	Model(const std::string& filePath);
	void Draw(Shader& shader);
	virtual ~Model(){}
private:
	std::vector<Mesh> meshes;
	void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory);
};


#endif