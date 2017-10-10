#include "AbstractGame.h"



AbstractGame::AbstractGame(State * state)
{
	this->state.push(state);
	MessageHandler::addSystemObject(this);
}


AbstractGame::~AbstractGame()
{
}

void AbstractGame::update(float dt)
{
	if (popState)
	{
		delete state.pop();
		popState = false;
	}
	state.peek()->update(dt);
}

void AbstractGame::render(Window * window)
{
	state.peek()->render(window);
}

void AbstractGame::executeMessages()
{
	state.peek()->executeMessages();

}

void AbstractGame::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case POPSTATE:
	{
		popState = true;
		if (state.capacity() <= 1)
			MessageHandler::postSystemMessage(new Message(QUIT));
		break;
	}
	case NEWSTATE:
	{
		NewStateMessage * sMsg = (NewStateMessage *)msg;
		state.push(sMsg->state);
		break;
	}
	default:
		break;
	}
}
