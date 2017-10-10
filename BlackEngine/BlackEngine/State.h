#pragma once
#include "Window.h"
#include "MessageHandler.h"
class State
{
public:
	MessageHandler * instance;
	~State();
	State();
	virtual void update(float dt);
	virtual void render(Window * window);
	void executeMessages();
};