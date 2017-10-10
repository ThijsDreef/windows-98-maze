#pragma once
#include "ShaderLoader.h"
#include "GameModel.h"
#include "TextureLoader.h"
#include "ObjParser.h"
#include "Matrix.h"
#include <include\SOIL.h>
class GraphicResourceManagement
{
private:
	unsigned int model;
	unsigned int camera;
	unsigned int texture;
	unsigned int projection;

	std::string currentShader;
	Matrix<float> perspectiveMatrix;
	Matrix<float> cameraMatrix;
	TextureLoader * textureLoader;
	GameModel * gameModel;
	ShaderLoader * shaderLoader;
	static GraphicResourceManagement * instance;
public:
	void requestShaderChange(std::string shaderName);
	void drawModel(const std::string & modelName, Matrix<float> & modelMatrix, bool wireFrame);
	void drawModelInstanced(const std::string & modelName, Matrix<float> * modelMatrices, bool wireFrame, int copies);
	void setCameraMatrix(Matrix<float> & cameraMatrix);
	void setTexture(std::string textureName);
	void init();
	static GraphicResourceManagement * getInstance();
	ShaderLoader * getShaderLoader();
	GameModel * getGameModel();
	TextureLoader * getTextureLoader();
	GraphicResourceManagement();
	~GraphicResourceManagement();
};

