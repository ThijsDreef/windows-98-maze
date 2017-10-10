#pragma once
#include "MessageHandler.h"
#include "TestState.h"
#include "Window.h"
class ParticleSpawner : public Object
{
private:
	MessageHandler * messageHandler;
public:
	ParticleSpawner(MessageHandler * instance,Vec3<float> loc);
	~ParticleSpawner();
	void handleMessage(Message * msg);
	void renderRequest();
};

