#include "State.h"

State::~State()
{
	delete instance;
}

State::State()
{
	instance = new MessageHandler();
}

void State::update(float dt)
{

}

void State::render(Window * window)
{
}
void State::executeMessages()
{
	instance->broadCastMessages();
	instance->handleSystemMessages();
	instance->handleGroups();
}
