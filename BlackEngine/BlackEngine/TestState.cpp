#include "TestState.h"



TestState::TestState()
{
	Camera * camera = new Camera(instance);
	Object * skybox = new skyBox(instance, camera);
	Maze * maze = new Maze(instance, 50, 50, camera);


}


TestState::~TestState()
{
}

void TestState::render(Window * window)
{
	instance->postToGroup(RENDERGROUP, new RenderRequest(window));
	RenderRequest * temp = new RenderRequest(window);
	temp->messageType = LATERENDER;
	instance->postToGroup(RENDERGROUP, temp);
}

void TestState::update(float dt)
{
	instance->postSystemMessage(new UpdateMessage(dt, instance));
	instance->postToGroup(UPDATEGROUP, new UpdateMessage(dt, instance));
}
