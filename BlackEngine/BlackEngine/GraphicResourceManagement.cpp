#include "GraphicResourceManagement.h"

GraphicResourceManagement * GraphicResourceManagement::instance = 0;

void GraphicResourceManagement::requestShaderChange(std::string shaderName)
{
	if (shaderName == currentShader) return;
	glUseProgram(shaderLoader->getShader(shaderName));
	camera = glGetUniformLocation(shaderLoader->getShader(shaderName), "view");
	texture = glGetUniformLocation(shaderLoader->getShader(shaderName), "tex");
	model = glGetUniformLocation(shaderLoader->getShader(shaderName), "model");
	projection = glGetUniformLocation(shaderLoader->getShader(shaderName), "projection");
	setCameraMatrix(cameraMatrix);
	currentShader = shaderName;
}

void GraphicResourceManagement::drawModel(const std::string & modelName, Matrix<float> & modelMatrix, bool wireFrame)
{
	if (wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix.matrix[0]);
	glBindVertexArray(gameModel->GetModel(modelName));
	int v = gameModel->GetVerticesCount(modelName);
	glDrawArrays(GL_TRIANGLES, 0, v);
	if (wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void GraphicResourceManagement::drawModelInstanced(const std::string & modelName, Matrix<float> * modelMatrices, bool wireFrame, int copies)
{
	if (wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(gameModel->GetModel(modelName));
	glBindBuffer(GL_ARRAY_BUFFER, gameModel->getVbos(modelName)[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * copies, &modelMatrices[0].matrix, GL_STATIC_DRAW);
	glDrawArraysInstanced(GL_TRIANGLES, 0, gameModel->GetVerticesCount(modelName), copies);
	if (wireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphicResourceManagement::setCameraMatrix(Matrix<float>& cameraMatrix)
{
	this->cameraMatrix = cameraMatrix;
	glUniformMatrix4fv(camera, 1, GL_FALSE, &cameraMatrix.matrix[0]);
	glUniformMatrix4fv(projection, 1, GL_FALSE, &perspectiveMatrix.matrix[0]);
}

void GraphicResourceManagement::setTexture(std::string textureName)
{
	//std::cout << glGetString(GL_ACTIVE_TEXTURE);
	glUniform1i(texture, textureLoader->getTexture(textureName));
}

void GraphicResourceManagement::init()
{
	perspectiveMatrix.perspectiveView(60, 1920.0f / 1080.0f, 0.001f, 100.0f);
	currentShader = "standard";
	ObjParser parser;
	gameModel = new GameModel();
	shaderLoader = new ShaderLoader();
	textureLoader = new TextureLoader();
	gameModel->createModel("skybox", parser.ParseObj("models/skybox.obj"));
	gameModel->createModel("cube", parser.ParseObj("models/wall.obj"));
	gameModel->createModel("particle", parser.ParseObj("models/particle.obj"));

	int width, height;
	textureLoader->createTexture(SOIL_load_image("textures/skybox.png", &width, &height, 0, SOIL_LOAD_RGBA), 4096, 4096, "left");
	textureLoader->createTexture(SOIL_load_image("textures/wall.png", &width, &height, 0, SOIL_LOAD_RGBA), 256, 256, "wall");
	textureLoader->createTexture(SOIL_load_image("textures/floor.png", &width, &height, 0, SOIL_LOAD_RGBA), 256, 256, "floor");
	textureLoader->createTexture(SOIL_load_image("textures/ceiling.png", &width, &height, 0, SOIL_LOAD_RGBA), 256, 256, "ceiling");



	shaderLoader->createShaderProgram("VertexShader.glsl", "fragmentshader.glsl", "standard");
	shaderLoader->createShaderProgram("textureVertexShader.glsl", "textureNoLightFrag.glsl", "skybox");
	shaderLoader->createShaderProgram("particleVertexShader.glsl", "patricleFragmentShader.glsl", "particles");

	glUseProgram(shaderLoader->getShader("standard"));
	texture = glGetUniformLocation(shaderLoader->getShader("skybox"), "tex");
	model = glGetUniformLocation(shaderLoader->getShader("standard"), "model");
	camera = glGetUniformLocation(shaderLoader->getShader("standard"), "view");
	projection = glGetUniformLocation(shaderLoader->getShader("standard"), "projection");
}

GraphicResourceManagement * GraphicResourceManagement::getInstance()
{
	if (!instance)
	{
		instance = new GraphicResourceManagement();
		instance->init();
	}
	return instance;
}

ShaderLoader * GraphicResourceManagement::getShaderLoader()
{
	return shaderLoader;
}

GameModel * GraphicResourceManagement::getGameModel()
{
	return gameModel;
}

TextureLoader * GraphicResourceManagement::getTextureLoader()
{
	return textureLoader;
}

GraphicResourceManagement::GraphicResourceManagement()
{
}


GraphicResourceManagement::~GraphicResourceManagement()
{
	delete gameModel;
	delete shaderLoader;
	delete textureLoader;
}
