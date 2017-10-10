#include "Message.h"


Message::~Message()
{
}

Message::Message()
{
	this->messageType = UNKNOWN;
}
Message::Message(int messageType, MessageHandler * messageHandler)
{
	this->messageType = messageType;
	this->messageHandler = messageHandler;
}
Message::Message(int messageType)
{
	this->messageType = messageType;
}
KeyMessage::KeyMessage(int key, bool down)
{
	this->messageType = KEY;
	this->key = key;
	this->down = down;
}

RenderRequest::RenderRequest(Window * window)
{
	this->window = window;
	this->messageType = RENDER;
}

AddCollision::AddCollision(CollisionBox collider, Matrix<float> * finalMatrix, std::string tag, int collisionType, Object * owner)
{
	this->collisionType = collisionType;
	this->tag = tag;
	this->coll = collider;
	this->finalMatrix = finalMatrix;
	this->messageType = ADDCOLLISION;
	this->owner = owner;
}

CollisionMessage::CollisionMessage(Object * other, std::string tag, Vec3<float> mid)
{
	this->mid = mid;
	this->tag = tag;
	this->other = other;
	this->messageType = COLLISION;
}

NewStateMessage::NewStateMessage(State * state)
{
	this->state = state;
	this->messageType = NEWSTATE;
}

UpdateMessage::UpdateMessage(float deltaTime, MessageHandler * instance)
{
	this->messageType = UPDATE;
	this->dt = deltaTime;
	this->messageHandler = instance;
}

MouseVelocityMessage::MouseVelocityMessage(float xvel, float yvel, int mouseX, int mouseY)
{
	this->messageType = MOUSEVELMESSAGE;
	this->xvel = xvel;
	this->yvel = yvel;
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}
