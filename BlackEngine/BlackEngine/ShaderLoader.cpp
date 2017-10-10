#include "ShaderLoader.h"



std::string ShaderLoader::readShader(char * fileName)
{
	std::string shaderCode;
	std::ifstream file(fileName, std::ios::in);
	if (!file.good())
	{
		std::cout << "cant read file" << fileName << std::endl;
		file.close();
	}
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

unsigned int ShaderLoader::CreateShader(GLenum shaderType, std::string source, char * shaderName)
{
	int compileResult = 0;
	unsigned int shader = glCreateShader(shaderType);
	const char * shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	//error check time
	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "error compiling shader: " << shaderName << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

unsigned int ShaderLoader::getShader(std::string shader)
{
	return shaderlist[shader];
}

void ShaderLoader::deleteShader(std::string shader)
{
	unsigned int p = shaderlist[shader];
	glDeleteProgram(p);
	shaderlist.erase(shader);
}

unsigned int ShaderLoader::createShaderProgram(char * vertexShaderPath, char * fragmentShaderPath, std::string shader)
{
	std::string vertexShaderCode = readShader(vertexShaderPath);
	std::string fragmentShaderCode = readShader(fragmentShaderPath);
	unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
	int linkResult = 0;
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> program_log(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &program_log[0]);
		std::cout << "Shader Loader : Link Error " << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	shaderlist[shader] = program;
	return program;
}

ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}
