#pragma once
#include "MessageHandler.h"
#include "Window.h"
class Box : public Object
{
private:
	int width, height;
	Matrix<float> * walls;
	Matrix<float> * floor;
	Matrix<float> * ceiling;
	int wallSize;
	int notWallSize;
public:
	Box(MessageHandler * instance, bool ** wall, int width, int height);
	void handleMessage(Message * msg);
	void renderRequest();
	~Box();
};

