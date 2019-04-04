#ifndef SHADER_H
#define SHADER_H

#include "transform.h"
#include "camera.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader(const std::string& filePath);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	std::string LoadShader(const std::string &fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];
};

#endif