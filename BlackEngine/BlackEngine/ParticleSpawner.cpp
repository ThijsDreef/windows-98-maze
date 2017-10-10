#include "ParticleSpawner.h"



ParticleSpawner::ParticleSpawner(MessageHandler * instance, Vec3<float> loc) : Object(instance)
{
	instance->subscribe(UPDATEGROUP, this);
	instance->subscribe(KEYMESSAGEGROUP, this);
	//instance->subscribe(RENDERGROUP, this);
	messageHandler = instance;
	shader = "standard";
	pos = loc;
}


ParticleSpawner::~ParticleSpawner()
{
}

void ParticleSpawner::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case KEY:
	{
		KeyMessage * kMsg = (KeyMessage*)msg;
		switch (kMsg->key)
		{
		case 27:
		{
			messageHandler->postSystemMessage(new Message(POPSTATE));
			// pop old state
			break;
		}
		case 9 :
		{
			// push new state
			messageHandler->postSystemMessage(new NewStateMessage(new TestState()));
			break;
		}
		case 32:
		{
			messageHandler->postToGroup(UPDATEGROUP, new Message(PARTICLEQUE));
			break;
		}
		default:
			break;
		}
		break;
	}
	case RENDER:
	{
		RenderRequest * rMsg = (RenderRequest*)msg;
		rMsg->window->RequestRender(this);
	}
	default:
		break;
	}
}

void ParticleSpawner::renderRequest()
{
	Matrix<float> temp;
	GraphicResourceManagement::getInstance()->drawModel("cube", temp, false);
}
