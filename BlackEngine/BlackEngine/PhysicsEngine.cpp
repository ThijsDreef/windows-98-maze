#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{
	MessageHandler::addSystemObject(this);
}

void PhysicsEngine::handleMessage(Message * msg)
{
	switch (msg->messageType)
	{
	case ADDCOLLISION:
	{
		AddCollision* col_msg = (AddCollision*)msg;
		collHolder temp;
		temp.coll = col_msg->coll;
		temp.collisionType = col_msg->collisionType;
		temp.matrix = col_msg->finalMatrix;
		temp.owner = col_msg->owner;
		temp.tag = col_msg->tag;
		temp.mid = Vec3<float>((temp.coll.high.x + temp.coll.low.x) / 2, (temp.coll.high.y + temp.coll.low.y) / 2, (temp.coll.high.z + temp.coll.low.z) / 2);

		if (temp.mid.x - temp.coll.low.x > temp.mid.y - temp.coll.low.y && temp.mid.x - temp.coll.low.x > temp.mid.z - temp.coll.low.z)
			temp.radius = temp.mid.x - temp.coll.low.x;
		else if (temp.mid.y - temp.coll.low.y > temp.mid.z - temp.coll.low.z)
			temp.radius = temp.mid.y - temp.coll.low.y;
		else
			temp.radius = temp.mid.z - temp.coll.low.z;
		collisions.push_back(temp);
		break;
	}
	case UPDATE:
	{
		for (int i = 0; i < collisions.size(); i++)
		{
			for (int j = (i + 1); j < collisions.size(); j++)
			{
				collisions[i].coll.low.plus(collisions[i].owner->pos);
				collisions[i].coll.high.plus(collisions[i].owner->pos);
				collisions[i].mid.plus(collisions[i].owner->pos);
				collisions[j].coll.low.plus(collisions[j].owner->pos);
				collisions[j].coll.high.plus(collisions[j].owner->pos);
				collisions[j].mid.plus(collisions[j].owner->pos);
				
				if (collisions[i].collisionType == BOX && collisions[j].collisionType == BOX)
				{
					if (boxToBox(collisions[i], collisions[j]))
					{
						collisions[i].owner->handleMessage(&CollisionMessage(collisions[j].owner, collisions[j].tag, collisions[j].mid));
						collisions[j].owner->handleMessage(&CollisionMessage(collisions[i].owner, collisions[i].tag, collisions[i].mid));
					}
				}
				else if (collisions[i].collisionType == CIRCLE && collisions[j].collisionType == CIRCLE)
				{
					if (circleToCircle(collisions[i], collisions[j]))
					{
						collisions[i].owner->handleMessage(&CollisionMessage(collisions[j].owner, collisions[j].tag, collisions[j].mid));
						collisions[j].owner->handleMessage(&CollisionMessage(collisions[i].owner, collisions[i].tag, collisions[i].mid));
					}
				}
				else
				{
					if (collisions[i].collisionType == CIRCLE)
					{
						if (boxToCircle(collisions[j], collisions[i]))
						{
							collisions[i].owner->handleMessage(&CollisionMessage(collisions[j].owner, collisions[j].tag, collisions[j].mid));
							collisions[j].owner->handleMessage(&CollisionMessage(collisions[i].owner, collisions[i].tag, collisions[i].mid));
						}
					}
					else
					{
						if (boxToCircle(collisions[i], collisions[j]))
						{
							collisions[i].owner->handleMessage(&CollisionMessage(collisions[j].owner, collisions[j].tag, collisions[j].mid));
							collisions[j].owner->handleMessage(&CollisionMessage(collisions[i].owner, collisions[i].tag, collisions[i].mid));
						}
					}
				}
				collisions[i].coll.low.minus(collisions[i].owner->pos);
				collisions[i].coll.high.minus(collisions[i].owner->pos);
				collisions[i].mid.minus(collisions[i].owner->pos);
				collisions[j].coll.low.minus(collisions[j].owner->pos);
				collisions[j].coll.high.minus(collisions[j].owner->pos);
				collisions[j].mid.minus(collisions[j].owner->pos);
			}
		}
		break;
	}
	default:
		break;
	}
}

bool PhysicsEngine::boxToBox(collHolder boxi, collHolder boxj)
{
	return (boxi.coll.high.x > boxj.coll.low.x &&
			boxi.coll.low.x < boxj.coll.high.x &&
			boxi.coll.high.y > boxj.coll.low.y &&
			boxi.coll.low.y < boxj.coll.high.y &&
			boxi.coll.high.z > boxj.coll.low.z &&
			boxi.coll.low.z < boxj.coll.high.z);
}

bool PhysicsEngine::circleToCircle(collHolder circlei, collHolder circlej)
{
	Vec3<float> distance(abs(circlei.mid.x - circlej.mid.x), abs(circlei.mid.y - circlej.mid.y), abs(circlei.mid.z - circlej.mid.z));
	distance.product(distance);
	if (circlei.tag == "zeppelin")
	{
		if (distance.x < 0.5f && distance.y < 0.5f && distance.z < 0.5f)
			std::cout << "collision detected";
	}
	return (distance.x + distance.y + distance.z <= pow(circlei.radius + circlej.radius, 2));
}

bool PhysicsEngine::boxToCircle(collHolder box, collHolder circle)
{
	float dmin = 0;
	if (circle.mid.x < box.coll.low.x)
		dmin += (circle.mid.x - box.coll.low.x) * (circle.mid.x - box.coll.low.x);
	else if (circle.mid.x > box.coll.high.x)
		dmin += (circle.mid.x - box.coll.high.x) * (circle.mid.x - box.coll.high.x);

	if (circle.mid.y < box.coll.low.y)
		dmin += (circle.mid.y - box.coll.low.y) * (circle.mid.y - box.coll.low.y);
	else if (circle.mid.y > box.coll.high.y)
		dmin += (circle.mid.y - box.coll.high.y) * (circle.mid.y - box.coll.high.y);

	if (circle.mid.z < box.coll.low.z)
		dmin += (circle.mid.z - box.coll.low.z) * (circle.mid.z - box.coll.low.z);
	else if (circle.mid.z > box.coll.high.z)
		dmin += (circle.mid.z - box.coll.high.z) * (circle.mid.z - box.coll.high.z);

	return dmin <= pow(circle.radius, 2);
}


PhysicsEngine::~PhysicsEngine()
{
}
