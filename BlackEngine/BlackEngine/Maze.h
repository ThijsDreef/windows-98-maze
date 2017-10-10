#pragma once
#include "Window.h"
#include "MessageHandler.h"
#include "Box.h"
class Maze : public Object
{
private:
	int width, height;
	bool ** walls;
	Object * player;
	const int minRooms = 20;
	int wallSize;
	void walk(int x, int y, bool ** visited, bool ** walls, int width, int height);
	void hunt(bool ** visited, bool ** walls, int width, int height);
	void destroyWalls(bool ** visited, bool ** walls, int width, int height, int x, int y, int dx, int dy);
	void createRooms(bool ** walls, int width, int height);
	std::vector<Vec2<int>> checkNeighbours(bool ** visited, int width, int height, int x, int y, bool good);
public:
	Maze(MessageHandler * instance, int width, int height, Object * player);
	void handleMessage(Message * msg);
	void renderRequest();
	~Maze();
};

