#include "FrameWork.h"
#include <iostream>
#include "AbstractGame.h"
int main()
{
	FrameWork * frameWork = new FrameWork();
	frameWork->start(new AbstractGame(new TestState()));
	frameWork->run();
	frameWork->stop();
	delete frameWork;
	return 0;
}