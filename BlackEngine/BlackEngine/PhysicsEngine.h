#pragma once
#include "MessageHandler.h"
#include "CollisionBox.h"
#include <math.h>
struct collHolder
{
	CollisionBox coll;
	Vec3<float> mid;
	float radius;
	int collisionType;
	std::string tag;
	Matrix<float> * matrix;
	Object * owner;
};
class PhysicsEngine : SystemObject
{
public:
	std::vector<collHolder> collisions;
	std::vector<collHolder> rawCollisionData;

	void handleMessage(Message * msg);
	bool boxToBox(collHolder boxi, collHolder boxj);
	bool circleToCircle(collHolder circlei, collHolder circlej);
	bool boxToCircle(collHolder box, collHolder circle);
	PhysicsEngine();
	~PhysicsEngine();
};

