#pragma once
#include <iostream>
#include <vector>
#include "Object.h"
#include "SystemObject.h"
enum groups
{
	PLAYERGROUP,
	UPDATEGROUP,
	MOUSEMESSAGEGROUP,
	KEYMESSAGEGROUP,
	RENDERGROUP,
	TOTALGROUPS
};
class MessageHandler
{
private:
	static std::vector<SystemObject*> systemObjects;
	static std::vector<Message*> systemMessageQue;
	std::vector<std::vector<Message*>> subscriptionQue;
	std::vector<std::vector<Object*>> objectSubscription;
	std::vector<Message*> broadCastQue;
	std::vector<Object *> allObjects;
public:
	~MessageHandler();
	MessageHandler();
	void subscribe(int group, Object* object);
	void postToGroup(int group, Message* msg);
	static void postSystemMessage(Message* msg);
	void handleSystemMessages();
	void handleGroups();
	void broadCastMessages();
	void addBroadCastMessage(Message* msg);
	static void addSystemObject(SystemObject * object);
	void addObject(Object * object);
};
	