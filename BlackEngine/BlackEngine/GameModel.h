#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "Matrix.h"
#include <include\GL\glew.h>
#include "VertexFormat.h"
#include "CollisionBox.h"

struct Model
{
	unsigned int verticesCount;
	unsigned int vao;
	std::vector<unsigned int> vbos;
	std::vector<VertexFormat> vertices;
	CollisionBox boxCollider;
};

class GameModel
{
public:
	void createModel(const std::string & gameModelName, std::vector<VertexFormat> & vertices);
	void DeleteModel(const std::string& gameModelName);
	unsigned int GetModel(const std::string& gameModelName);
	unsigned int GetVerticesCount(const std::string & gameModelName);
	std::vector<unsigned int> getVbos(const std::string & gameModelName);
	CollisionBox getCollisionBox(const std::string & gameModelName);
	GameModel();
	~GameModel();
private:
	std::map<std::string, Model> GameModelList;
	std::map<std::string, CollisionBox> collisionBoxList;
};

