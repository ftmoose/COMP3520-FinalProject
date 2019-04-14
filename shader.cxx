#include "shader.h"

Shader::Shader(const std::string& filePath)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(filePath + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(filePath + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "ERROR::PROGRAM::LINKING:");
	
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");

}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(program);
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "ERROR::SHADER::CREATION::FAILURE" << std::endl;

	const GLchar* shaderSourceArr[1];
	shaderSourceArr[0] = text.c_str();
	glShaderSource(shader, 1, shaderSourceArr, NULL);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR::SHADER::COMPILATION:");

	return shader;
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 trans = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &trans[0][0]);
}

std::string Shader::LoadShader(const std::string &fileName)
{

	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(fileName);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char *finalShaderCode = shaderCode.c_str();

	return finalShaderCode;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage)
{
	int success = 0;
	char error[1024] = {0};

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}



void Shader::setBool(const std::string &name, bool value) const
{         
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{ 
	glUniform1i(glGetUniformLocation(program, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{ 
	glUniform1f(glGetUniformLocation(program, name.c_str()), value); 
}
// -------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value.x);
}