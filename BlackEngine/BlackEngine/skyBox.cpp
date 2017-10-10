#include "skyBox.h"



skyBox::skyBox(MessageHandler * instance, Object * camera) : Object(instance)
{
	cam = camera;
	shader = "skybox";
	angle = 45;
	instance->subscribe(UPDATEGROUP, this);
	instance->subscribe(RENDERGROUP, this);
}


skyBox::~skyBox()
{
}

void skyBox::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case RENDER:
	{
		RenderRequest * render_msg = (RenderRequest*)msg;
		render_msg->window->RequestRender(this);
		break;
	}
	case UPDATE:
	{
		break;
	}
	default:
		break;
	}
}

void skyBox::renderRequest()
{
	angle += 0.1f;
	Matrix<float> temp;
	Matrix<float> translation;
	translation.translateMatrix(Vec3<float>(-cam->pos.x, -cam->pos.y, -cam->pos.z));
	temp.scaleMatrix(Vec3<float>(50, 50, 50));
	temp = translation.multiplyByMatrix(temp);
	glDepthMask(0);
	GraphicResourceManagement::getInstance()->setTexture("left");
	GraphicResourceManagement::getInstance()->drawModel("skybox", temp, false);
	glDepthMask(1);
}
