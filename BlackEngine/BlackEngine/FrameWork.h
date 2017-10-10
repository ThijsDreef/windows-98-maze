#pragma once
#include <thread>
#include <stdlib.h>
#include "AbstractGame.h"
#include "SystemObject.h"
#include "KeyHandler.h"
#include "MessageHandler.h"
#include "Window.h"
#include "PhysicsEngine.h"
#include <time.h>

class FrameWork : public SystemObject
{
private:
	PhysicsEngine * pe;
	KeyHandler * keyHandler;
	Window * window;
	bool running = false;
	AbstractGame * game;
public:
	FrameWork();
	~FrameWork();
	bool start(AbstractGame * Game);
	void run();
	void stop();
	void handleMessage(Message* msg);
};

