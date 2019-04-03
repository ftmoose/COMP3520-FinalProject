#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	Texture(const std::string& filePath);
	void Bind(unsigned int unit);
	inline GLuint getTexture() { return texture; }
	virtual ~Texture();
private:
	GLuint texture;
};

#endif