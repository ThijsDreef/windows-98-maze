#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
struct VertexFormat
{
	Vec3<float> position;
	Vec4<float> color;
	Vec3<float> normal;
	Vec2<float> uv;
	VertexFormat(const Vec3<float> &pos, const Vec4<float> &col, Vec3<float> &norm, Vec2<float> texture)
	{
		position = pos;
		color = col;
		uv = texture;
		normal = norm;
	}
};