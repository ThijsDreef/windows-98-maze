#pragma once
#include "Message.h"
class SystemObject
{
public:
	virtual void handleMessage(Message* msg) = 0;
};