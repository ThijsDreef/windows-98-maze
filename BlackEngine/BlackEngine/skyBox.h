#pragma once
#include "MessageHandler.h"
#include "Window.h"
class skyBox : public Object
{
public:
	skyBox(MessageHandler * instance, Object * camera);
	~skyBox();
	Object * cam;
	void handleMessage(Message * msg);
	void renderRequest();
	float angle;
};

