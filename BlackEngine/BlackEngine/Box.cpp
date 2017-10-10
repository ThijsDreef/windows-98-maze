#include "Box.h"


Box::Box(MessageHandler * instance, bool ** wall, int width, int height) : Object(instance)
{
	wallSize = 0;
	notWallSize = 0;
	walls = new Matrix<float>[width * height];
	ceiling = new Matrix<float>[width * height];
	floor = new Matrix<float>[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (wall[x][y])
			{
				walls[wallSize].translateMatrix(Vec3<float>(x * 2, 0, y * 2));
				wallSize++;
			}
			else
			{
				ceiling[notWallSize].translateMatrix(Vec3<float>(x * 2, 2, y * 2));
				floor[notWallSize].translateMatrix(Vec3<float>(x * 2, -2, y * 2));
				notWallSize++;
			}
		}
	}
	shader = "particles";
	instance->subscribe(RENDERGROUP, this);
	this->pos = pos;
}

void Box::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case RENDER:
	{
		RenderRequest * rmsg = (RenderRequest *)msg;
		rmsg->window->RequestRender(this);
	}
	default:
		break;
	}
}

void Box::renderRequest()
{
	GraphicResourceManagement::getInstance()->setTexture("wall");
	GraphicResourceManagement::getInstance()->drawModelInstanced("cube", walls, false, wallSize);
	GraphicResourceManagement::getInstance()->setTexture("ceiling");
	GraphicResourceManagement::getInstance()->drawModelInstanced("cube", ceiling, false, notWallSize);
	GraphicResourceManagement::getInstance()->setTexture("floor");
	GraphicResourceManagement::getInstance()->drawModelInstanced("cube", floor, false, notWallSize);

}

Box::~Box()
{

}
