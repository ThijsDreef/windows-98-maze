#include "TextureLoader.h"



void TextureLoader::createTexture(unsigned char * pixels, int width, int height, std::string textureNmae)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + textureList.size());
	//std::cout << std::endl << "texture number is : " << texture << std::endl;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//std::cout << std::endl << "texture number is : " << texture << std::endl;
	textureList[textureNmae] = textureList.size();
}

unsigned int TextureLoader::getTexture(std::string texture)
{
	return textureList[texture];
}

void TextureLoader::deleteTexture(std::string texture)
{
	glDeleteTextures(1, &textureList[texture]);
	textureList.erase(texture);
}

TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
	std::map<std::string, unsigned int>::iterator it;
	for (it = textureList.begin(); it != textureList.end(); ++it)
	{
		unsigned int * p = &it->second;
		glDeleteTextures(1, p);
	}
	textureList.clear();
}
