#include "Maze.h"

void Maze::walk(int x, int y, bool ** visited, bool ** walls, int width, int height)
{
	std::vector<Vec2<int>> choices = checkNeighbours(visited, width, height, x, y, true);
	if (choices.size() != 0)
	{
		int index = rand() % choices.size();
		destroyWalls(visited, walls, width, height, x, y, choices[index].x, choices[index].y);
		walk(x + choices[index].x, y + choices[index].y, visited, walls, width, height);
	}
	hunt(visited, walls, width, height);
}

void Maze::hunt(bool ** visited, bool ** walls, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (!visited[x][y])
			{
				std::vector<Vec2<int>> choices = checkNeighbours(visited, width, height, x, y, false);
				if (choices.size() != 0)
				{
					int index = rand() % choices.size();
					destroyWalls(visited, walls, width, height, x, y, choices[index].x, choices[index].y);
					walk(x + choices[index].x, y + choices[index].y, visited, walls, width, height);
					return;
				}
			}
		}
	}
}

void Maze::destroyWalls(bool ** visited, bool ** walls, int width, int height, int x, int y, int dx, int dy)
{
	visited[x][y] = true;
	walls[1 + x * 2][1 + y * 2] = false;
	walls[1 + (x * 2) + dx][1 + (y * 2) + dy] = false;
}

void Maze::createRooms(bool ** walls, int width, int height)
{
	int factor = width / 4;
	for (int i = 0; i < minRooms + factor; i++)
	{
		int offx = 1 + rand() % (width - 4);
		int offy = 1 + rand() % (height - 4);
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				walls[x + offx][y + offy] = false;
			}
		}
	}
	for (int x = 1; x < width; x++)
	{
		for (int y = 1; y < height; y++)
		{
			if (walls[x][y])
			{
				int neighbours = checkNeighbours(walls, width, height, x, y, true).size();
				if (neighbours == 0)
				{
					walls[x][y] = false;
				}
			}
		}
	}
}

std::vector<Vec2<int>> Maze::checkNeighbours(bool ** visited, int width, int height, int x, int y, bool good)
{
	std::vector<Vec2<int>> choices = std::vector<Vec2<int>>();
	if (x != width - 1)
		if (good && !visited[x + 1][y] || !good && visited[x + 1][y])
			choices.push_back(Vec2<int>(1, 0));
	if (x != 0)
		if (good && !visited[x - 1][y] || !good && visited[x - 1][y])
			choices.push_back(Vec2<int>(-1, 0));
	if (y != height- 1)
		if (good && !visited[x][y + 1] || !good && visited[x][y + 1])
			choices.push_back(Vec2<int>(0, 1));
	if (y != 0)
		if (good && !visited[x][y -1] || !good && visited[x][y - 1])
			choices.push_back(Vec2<int>(0, -1));
	return choices;
}


Maze::Maze(MessageHandler * instance, int width, int height, Object * player) : Object(instance)
{
	this->player = player;
	srand(time(NULL));
	shader = "maze";
	bool ** visited = new bool * [width];
	walls = new bool *[1 + (width) * 2];
	// creating the 2d arrays with init values
	for (int i = 0; i < width; i++)
	{
		visited[i] = new bool[height];
		for (int j = 0; j < height; j++)
			visited[i][j] = false;
	}
	for (int i = 0; i < 1 +(width) * 2; i++)
	{
		walls[i] = new bool[1 + (height) * 2];
		for (int j = 0; j < 1 + (height) * 2; j++)
			walls[i][j] = true;
	}
	walk(width / 2, height / 2, visited, walls, width, height);
	//printing the walls array
	createRooms(walls, width * 2, height * 2);
	for (int y = 0; y < height * 2 + 1; y++)
	{
		for (int x = 0; x < width * 2 + 1; x++)
		{
			std::cout << walls[x][y] << " ";
		}
		std::cout << std::endl;
	}
	new Box(instance, walls, 1 + width * 2, 1 + height * 2);
	//cleanup
	for (int i = 0; i < width; i++)
	{
		delete[] visited[i];
	}
	delete[] visited;
	instance->subscribe(UPDATEGROUP, this);
}

void Maze::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case UPDATE:
	{
		int posx = nearbyint(-player->pos.x / 2);
		int posy = nearbyint(-player->pos.z / 2);
		if (walls[posx][posy])
		{
			std::cout << "executed";
			player->handleMessage(new Message(RESOLVE));
		}
	}
	default:
		break;
	}
}

void Maze::renderRequest()
{

}

Maze::~Maze()
{
	for (int i = 0; i < 1 + width * 2; i++)
	{
		delete[] walls[i];
	}
	delete[] walls;
}
