#include "MessageHandler.h"

std::vector<SystemObject*> MessageHandler::systemObjects;
std::vector<Message*> MessageHandler::systemMessageQue;
MessageHandler::~MessageHandler()
{
	for (int i = 0; i < subscriptionQue.size(); i++)
	{
		for (int j = 0; j < subscriptionQue[i].size(); j++)
		{
			delete subscriptionQue[i][j];
		}
	}
	for (int i = 0; i < broadCastQue.size(); i++)
	{
		delete broadCastQue[i];
	}
	for (int i = 0; i < allObjects.size(); i++)
	{
		delete allObjects[i];
	}
}
MessageHandler::MessageHandler()
{
	for (int i = 0; i < TOTALGROUPS; i++)
	{
		subscriptionQue.push_back(std::vector<Message*>());
		objectSubscription.push_back(std::vector<Object*>());
	}
}
void MessageHandler::subscribe(int group, Object* object)
{
	objectSubscription.at(group).push_back(object);
}

void MessageHandler::postToGroup(int group, Message* msg)
{
	subscriptionQue.at(group).push_back(msg);
}

void MessageHandler::postSystemMessage(Message * msg)
{
	systemMessageQue.push_back(msg);
}

void MessageHandler::handleSystemMessages()
{
	for (int i = 0; i < systemMessageQue.size(); i++)
	{
		for (int j = 0; j < systemObjects.size(); j++)
		{
			if (systemMessageQue[i])
			{
				systemObjects.at(j)->handleMessage(systemMessageQue.at(i));
			}
		}
		delete systemMessageQue[i];
	}
	int size = systemMessageQue.size();
	systemMessageQue.clear();
	systemMessageQue.reserve(size);
}

void MessageHandler::handleGroups()
{
	for (int i = 0; i < subscriptionQue.size(); i++)
	{
		for (int j = 0; j < subscriptionQue.at(i).size(); j++)
		{
			for (int t = 0; t < objectSubscription.at(i).size(); t++)
			{
				objectSubscription.at(i).at(t)->handleMessage(subscriptionQue.at(i).at(j));
			}
			delete subscriptionQue[i].at(j);
		}
		int size = subscriptionQue.size();
		subscriptionQue.at(i).clear();
		subscriptionQue.at(i).reserve(size);
	}
}

void MessageHandler::broadCastMessages()
{
	for (int i = 0; i < broadCastQue.size(); i++)
	{
		for (int j = 0; j < allObjects.size(); j++)
		{
			allObjects[j]->handleMessage(broadCastQue[i]);
		}
	}
}

void MessageHandler::addBroadCastMessage(Message* msg)
{
	broadCastQue.push_back(msg);
}

void MessageHandler::addSystemObject(SystemObject * object)
{
	systemObjects.push_back(object);
}

void MessageHandler::addObject(Object * object)
{
	allObjects.push_back(object);
}
