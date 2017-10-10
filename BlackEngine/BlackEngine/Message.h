#pragma once
#include <iostream>
#include <String>
#include "CollisionBox.h"
#include "Matrix.h"
class Object;
class Window;
class State;
class MessageHandler;
enum MessageType
{
	UNKNOWN,
	KEY,
	QUIT,
	RENDER,
	MOUSEVELMESSAGE,
	LATERENDER,
	UPDATE,
	ADDCOLLISION,
	PARTICLEQUE,
	COLLISION,
	NEWSTATE,
	POPSTATE,
	RESOLVE
};
class Message
{
public:
	virtual ~Message();
	Message();
	Message(int messageTyp, MessageHandler * messageHandler);
	Message(int messageType);
	MessageHandler * messageHandler;
	int messageType;
};
class KeyMessage : public Message
{
public:
	KeyMessage(int key, bool down);
	int key;
	bool down;
};
class RenderRequest : public Message
{
public:
	RenderRequest(Window * window);
	Window* window;
};
class AddCollision : public Message
{
public:
	AddCollision(CollisionBox collider, Matrix<float> * finalMatrix, std::string tag, int collisionType, Object * owner);
	CollisionBox coll;
	int collisionType;
	Matrix<float> * finalMatrix;
	std::string tag;
	Object * owner;
};
class CollisionMessage : public Message
{
public:
	CollisionMessage(Object * other, std::string tag, Vec3<float> mid);
	Object * other;
	std::string tag;
	Vec3<float> mid;
};
class NewStateMessage : public Message
{
public:
	NewStateMessage(State * state);
	State * state;
};
class MouseVelocityMessage : public Message
{
public:
	MouseVelocityMessage(float xvel, float yvel, int mouseX, int mouseY);
	float xvel;
	float yvel;
	int mouseX;
	int mouseY;
};
class UpdateMessage : public Message
{
public:
	UpdateMessage(float deltaTime, MessageHandler * instance);
	float dt;
};