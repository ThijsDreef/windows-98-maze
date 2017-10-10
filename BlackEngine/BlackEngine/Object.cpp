#include "Object.h"
#include "MessageHandler.h"

Object::Object(MessageHandler * instance)
{
	instance->addObject(this);
}

Object::~Object()
{
}
