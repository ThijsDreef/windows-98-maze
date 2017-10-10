#pragma once
#include "MessageHandler.h"
#include "Camera.h"
#include "State.h"
#include "skyBox.h"
#include "Box.h"
#include "Maze.h"
#include "ParticleSpawner.h"
#include "ParticleSystem.h"
class TestState : public State
{
public:
	TestState();
	~TestState();
	void render(Window * window);
	void update(float dt);
};

