#pragma once
#include <map>
#include <string>
#include <vector>
#include <include\GL\glew.h>
#include <iostream>

class TextureLoader
{
private:
	std::map<std::string, unsigned int> textureList;
public:
	void createTexture(unsigned char * pixels, int width, int height, std::string textureNmae);
	unsigned int getTexture(std::string texture);
	void deleteTexture(std::string texture);
	TextureLoader();
	~TextureLoader();
};

