#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	Texture();
	Texture(const std::string& filePath);
	void Bind(unsigned int unit);
	inline GLuint getTexture() { return texture; }

	inline std::string GetType() 	{ return type; }
	inline GLuint GetTex() 			{ return texture; }
	inline std::string GetPath() 			{ return path; }

	inline void SetType(const std::string& t) 	{ type = t; }
	inline void SetTex(GLuint tex) 				{ texture = tex; }
	inline void SetPath(const std::string& p) 	{ path = p; }

private:
	GLuint texture;
	std::string type;
	std::string path;
};

#endif