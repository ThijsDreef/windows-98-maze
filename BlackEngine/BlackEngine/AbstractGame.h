#pragma once
#include "MessageHandler.h"
#include "State.h"
#include "Stack.h"
#include "Window.h"
#include "TestState.h"
class AbstractGame : public SystemObject
{
private:
	Stack<State*> state = Stack<State*>();
	bool popState;
public:
	AbstractGame(State * state);
	~AbstractGame();
	void update(float dt);
	void render(Window * window);
	void handleMessage(Message * msg);
	void executeMessages();
};

