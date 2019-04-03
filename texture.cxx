#include "texture.h"

Texture::Texture(const std::string &filePath)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &numComponents, 4);

	if (!imageData) {
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return;
	}

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture); 
}

void Texture::Bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit); 
	glBindTexture(GL_TEXTURE_2D, texture);
}