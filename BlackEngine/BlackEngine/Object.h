#pragma once
#include "Message.h"
#include "GraphicResourceManagement.h"
#include "Vec3.h"
#include <list>
class MessageHandler;
class Object
{
private:
	long refCount;
public:
	std::string tag;
	std::string shader;
	Vec3<float> pos;
	Vec3<float> rot;
	Object(MessageHandler * instance);
	~Object();
	virtual void handleMessage(Message * msg) = 0;
	virtual void renderRequest() = 0;
};