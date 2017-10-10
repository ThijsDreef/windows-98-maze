#include "KeyHandler.h"



KeyHandler::KeyHandler()
{
	MessageHandler::addSystemObject(this);
	for (int i = 0; i < 256; i++)
	{
		keys[i] = false;
	}
	mousex = 0;
	mousey = 0;
	mouseXvel = 0;
	mouseYvel = 0;
}


KeyHandler::~KeyHandler()
{
}

void KeyHandler::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
		case UNKNOWN:
		{
			break;
		}
		case KEY:
		{
			KeyMessage* key_msg = (KeyMessage*)msg;
			if (key_msg->down)
				keys[key_msg->key] = true;
			else
				keys[key_msg->key] = false;
			break;
		}
		case MOUSEVELMESSAGE:
		{
			MouseVelocityMessage * mvmsg = (MouseVelocityMessage*)msg;
			mousex = mvmsg->mouseX;
			mousey = mvmsg->mouseY;
			mouseXvel = mvmsg->xvel;
			mouseYvel = mvmsg->yvel;
			break;
		}
		case UPDATE:
		{
			for (int i = 0; i < 256; i++)
			{
				if (keys[i])
					msg->messageHandler->postToGroup(KEYMESSAGEGROUP, new KeyMessage(i, true));
			}
			msg->messageHandler->postToGroup(MOUSEVELMESSAGE, new MouseVelocityMessage(mouseXvel, mouseYvel, mousex, mousey));
			break;
		}
		default:
			break;
	}
}
