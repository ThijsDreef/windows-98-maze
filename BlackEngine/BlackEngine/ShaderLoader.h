#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <include\GL\glew.h>
class ShaderLoader
{
private:
	std::map<std::string, unsigned int> shaderlist;
	std::string readShader(char* fileName);
	unsigned int CreateShader(GLenum shaderType, std::string source, char* shadername);
public:
	unsigned int getShader(std::string shader);
	void deleteShader(std::string shader);
	unsigned int createShaderProgram(char* vertexShaderPath, char* fragmentShaderPath, std::string shader);
	ShaderLoader();
	~ShaderLoader();
};

