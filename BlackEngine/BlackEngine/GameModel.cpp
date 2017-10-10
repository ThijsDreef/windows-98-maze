#include "GameModel.h"

void GameModel::createModel(const std::string & gameModelName, std::vector<VertexFormat>& vertices)
{
	if (vertices.size() == 0)
		return;
	unsigned int vao;
	unsigned int vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)28);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)40);
	unsigned int instanceVbo;
	glGenBuffers(1, &instanceVbo);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix<float>), (void*)0);
	glVertexAttribDivisor(4, 1);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix<float>), (void*)(sizeof(float) * 4));
	glVertexAttribDivisor(5, 1);

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix<float>), (void*)(sizeof(float) * 4 * 2));
	glVertexAttribDivisor(6, 1);

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix<float>), (void*)(sizeof(float) * 4* 3));
	glVertexAttribDivisor(7, 1);

	Model temp;
	temp.vao = vao;
	temp.vbos.push_back(vbo);
	temp.vbos.push_back(instanceVbo);
	temp.verticesCount = vertices.size();
	temp.vertices = vertices;
	Vec3<float> low(0, 0, 0);
	Vec3<float> high(0, 0, 0);
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.x > high.x)
			high.x = vertices[i].position.x;
		else if (vertices[i].position.x < low.x)
			low.x = vertices[i].position.x;

		if (vertices[i].position.y > high.y)
			high.y = vertices[i].position.y;
		else if (vertices[i].position.y < low.y)
			low.y = vertices[i].position.y;

		if (vertices[i].position.z > high.z)
			high.z = vertices[i].position.z;
		else if (vertices[i].position.z < low.z)
			low.z = vertices[i].position.z;
	}
	temp.boxCollider.low = low;
	temp.boxCollider.high = high;
	GameModelList[gameModelName] = temp;
	collisionBoxList[gameModelName] = temp.boxCollider;
	GLenum err;
}

void GameModel::DeleteModel(const std::string & gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int GameModel::GetModel(const std::string & gameModelName)
{
	return GameModelList[gameModelName].vao;
}

unsigned int GameModel::GetVerticesCount(const std::string & gameModelName)
{
	return GameModelList[gameModelName].verticesCount;
}

std::vector<unsigned int> GameModel::getVbos(const std::string & gameModelName)
{
	return GameModelList[gameModelName].vbos;
}

CollisionBox GameModel::getCollisionBox(const std::string & gameModelName)
{
	return collisionBoxList[gameModelName];
}

GameModel::GameModel()
{
}


GameModel::~GameModel()
{
	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		//delete VAO and VBOs (if many)
		unsigned int * p = &it->second.vao;
		std::cout << *p;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}
