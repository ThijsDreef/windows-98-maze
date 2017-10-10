#pragma once
#include "MessageHandler.h"
#include <atomic>
class KeyHandler : public SystemObject
{
private:
	std::atomic<bool> keys[256];
	std::atomic<float> mouseXvel;
	std::atomic<float> mouseYvel;
	std::atomic<int> mousex;
	std::atomic<int> mousey;
public:
	KeyHandler();
	~KeyHandler();
	void handleMessage(Message * msg);
};

