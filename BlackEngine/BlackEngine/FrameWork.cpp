#include "FrameWork.h"

FrameWork::FrameWork()
{
	MessageHandler::addSystemObject(this);
}


FrameWork::~FrameWork()
{

}

bool FrameWork::start(AbstractGame * Game)
{
	
	srand(clock());
	game = Game;
	window = new Window();
	pe = new PhysicsEngine();
	keyHandler = new KeyHandler();
	std::thread t1([=] {window->createGlWindow("title", 1920, 1080, 32, true, keyHandler); });
	t1.detach();
	window->update = true;
	running = true;
	return true;
}

void FrameWork::run()
{
	clock_t timer = clock();
	float elapsedTime = 0;
	float logicLoop = 0;
	float time;
	int frames = 0;
	float logicCap = (float)1 / 60;
	float deltaTime = 0;
	float oldDeltaTime = 0;
	bool render = false;
	while (running)
	{
		time = clock() - timer;
		elapsedTime += time / CLOCKS_PER_SEC;
		logicLoop += time / CLOCKS_PER_SEC;
		deltaTime += time / CLOCKS_PER_SEC;
		timer = clock();
		if (elapsedTime >= 1)
		{
			elapsedTime = 0;
			std::cout << "frames per second : " << frames << std::endl;
			frames = 0;
		}
		if (!window->update)
		{
			oldDeltaTime = deltaTime;
			deltaTime = 0;
			game->update(oldDeltaTime);
			game->render(window);
			game->executeMessages();
			logicLoop -= logicCap;
			frames++;
			window->update = true;
		}
		
		
	}
	window->update = false;
}

void FrameWork::stop()
{
	window->done = true;
	delete keyHandler;
	delete game;
	delete pe;
}

void FrameWork::handleMessage(Message * msg)
{
	if (msg->messageType == QUIT)
		running = false;
}
