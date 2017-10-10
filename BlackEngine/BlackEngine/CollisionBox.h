#pragma once
#include "Vec3.h"
enum collisionType
{
	BOX,
	CIRCLE
};
struct CollisionBox
{
	Vec3<float> low;
	Vec3<float> high;
};