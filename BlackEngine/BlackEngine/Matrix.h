#pragma once
#include "Vec3.h"
#include "Vec4.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<vector>
enum axis
{
	X,Y,Z
};
template <class T>
class Matrix
{
private:
	void resetMatrix();
public:
	void debug();
	T matrix[16];
	void translateMatrix(Vec3<T> vec);
	void perspectiveView(float fov, float aspect, float zNear, float zFar);
	void orthographicView(float width, float height, float zNear, float zFar);
	void rotation(T angle , int axis);
	void scaleMatrix(Vec3<T> vec);
	Matrix();
	~Matrix();
	Matrix<T> multiplyByMatrix(Matrix<T> otherMatrix);
	Vec3<T> multiplyByVector(Vec3<T> vec);
	Vec3<T> translateVector(Vec3<T> vec);
};

template<class T>
inline void Matrix<T>::resetMatrix()
{
	for (int i = 0; i < 16; i++)
		matrix[i] = 0;
}

template<class T>
inline void Matrix<T>::debug()
{
	for (int i = 0; i < 16; i++)
		std::cout << i << " " << matrix[i] << std::endl;
}

template<class T>
inline void Matrix<T>::translateMatrix(Vec3<T> vec)
{
	resetMatrix();
	matrix[0] = 1;
	matrix[5] = 1;
	matrix[10] = 1;
	matrix[12] = vec.x;
	matrix[13] = vec.y;
	matrix[14] = vec.z;
	matrix[15] = 1;
}

template<class T>
inline void Matrix<T>::perspectiveView(float fov, float aspect, float zNear, float zFar)
{
	resetMatrix();
	float fovY = fov * M_PI / 180.0f;
	float tangent = tanf(fovY / 2 ); // tangent of half fovY
	float height = zNear * tangent;         // half height of near plane
	float width = height * aspect;   // half width of near plane

	matrix[0] = 2 * zNear / (width - -width);
	matrix[5] = 2 * zNear / (height - -height);
	matrix[8] = (width + -width) / (width - -width);
	matrix[9] = (height + -height) / (height - -height);
	matrix[10] = -(zFar + zNear) / (zFar - zNear);
	matrix[11] = -1;
	matrix[14] = -(2 * zFar * zNear) / (zFar - zNear);
}

template<class T>
inline void Matrix<T>::orthographicView(float width, float height, float zNear, float zFar)
{
	matrix = new T[16]
			{ 1 / width, 0, 0, 0,
			  0, 1 / height, 0, 0
			  0, 0, -(2 / (zFar - zNear)), -((zFar + zNear)/zFar-zNear),
			  0, 0, 0, 1 };
}

template<class T>
inline void Matrix<T>::rotation(T angle, int axis)
{
	resetMatrix();
	float radians = angle * M_PI / 180.0f;
	if (axis == X)
	{
		matrix[0] = 1;
		matrix[5] = cos(radians);
		matrix[6] = -sin(radians);
		matrix[9] = sin(radians);
		matrix[10] = cos(radians);
		matrix[15] = 1;
	}
	else if (axis == Y)
	{
		matrix[0] = cos(radians);
		matrix[2] = sin(radians);
		matrix[5] = 1;
		matrix[8] = -sin(radians);
		matrix[10] = cos(radians);
		matrix[15] = 1;
	}
	else if (axis == Z)
	{
		matrix[0] = cos(radians);
		matrix[1] = -sin(radians);
		matrix[4] = sin(radians);
		matrix[5] = cos(radians);
		matrix[10] = 1;
		matrix[15] = 1;
	}
}

template<class T>
inline void Matrix<T>::scaleMatrix(Vec3<T> vec)
{
	resetMatrix();
	matrix[0] = vec.x;
	matrix[5] = vec.y;
	matrix[10] = vec.z;
	matrix[15] = 1;
}

template<class T>
inline Matrix<T>::Matrix()
{
	matrix[0] = 1;
	matrix[6] = 1;
	matrix[11] = 1;
	matrix[15] = 1;
}

template<class T>
inline Matrix<T>::~Matrix()
{

}

template<class T>
inline Matrix<T> Matrix<T>::multiplyByMatrix(Matrix<T> otherMatrix)
{
	Matrix<T> temp;
	temp.matrix[0] = matrix[0] * otherMatrix.matrix[0] + matrix[4] * otherMatrix.matrix[1] + matrix[8] * otherMatrix.matrix[2] + matrix[12] * otherMatrix.matrix[3];
	temp.matrix[1] = matrix[1] * otherMatrix.matrix[0] + matrix[5] * otherMatrix.matrix[1] + matrix[9] * otherMatrix.matrix[2] + matrix[13] * otherMatrix.matrix[3];
	temp.matrix[2] = matrix[2] * otherMatrix.matrix[0] + matrix[6] * otherMatrix.matrix[1] + matrix[10] * otherMatrix.matrix[2] + matrix[14] * otherMatrix.matrix[3];
	temp.matrix[3] = matrix[3] * otherMatrix.matrix[0] + matrix[7] * otherMatrix.matrix[1] + matrix[11] * otherMatrix.matrix[2] + matrix[15] * otherMatrix.matrix[3];

	temp.matrix[4] = matrix[0] * otherMatrix.matrix[4] + matrix[4] * otherMatrix.matrix[5] + matrix[8] * otherMatrix.matrix[6] + matrix[12] * otherMatrix.matrix[7];
	temp.matrix[5] = matrix[1] * otherMatrix.matrix[4] + matrix[5] * otherMatrix.matrix[5] + matrix[9] * otherMatrix.matrix[6] + matrix[13] * otherMatrix.matrix[7];
	temp.matrix[6] = matrix[2] * otherMatrix.matrix[4] + matrix[6] * otherMatrix.matrix[5] + matrix[10] * otherMatrix.matrix[6] + matrix[14] * otherMatrix.matrix[7];
	temp.matrix[7] = matrix[3] * otherMatrix.matrix[4] + matrix[7] * otherMatrix.matrix[5] + matrix[11] * otherMatrix.matrix[6] + matrix[15] * otherMatrix.matrix[7];

	temp.matrix[8] = matrix[0] * otherMatrix.matrix[8] + matrix[4] * otherMatrix.matrix[9] + matrix[8] * otherMatrix.matrix[10] + matrix[12] * otherMatrix.matrix[11];
	temp.matrix[9] = matrix[1] * otherMatrix.matrix[8] + matrix[5] * otherMatrix.matrix[9] + matrix[9] * otherMatrix.matrix[10] + matrix[13] * otherMatrix.matrix[11];
	temp.matrix[10] = matrix[2] * otherMatrix.matrix[8] + matrix[6] * otherMatrix.matrix[9] + matrix[10] * otherMatrix.matrix[10] + matrix[14] * otherMatrix.matrix[11];
	temp.matrix[11] = matrix[3] * otherMatrix.matrix[8] + matrix[7] * otherMatrix.matrix[9] + matrix[11] * otherMatrix.matrix[10] + matrix[15] * otherMatrix.matrix[11];

	temp.matrix[12] = matrix[0] * otherMatrix.matrix[12] + matrix[4] * otherMatrix.matrix[13] + matrix[8] * otherMatrix.matrix[14] + matrix[12] * otherMatrix.matrix[15];
	temp.matrix[13] = matrix[1] * otherMatrix.matrix[12] + matrix[5] * otherMatrix.matrix[13] + matrix[9] * otherMatrix.matrix[14] + matrix[13] * otherMatrix.matrix[15];
	temp.matrix[14] = matrix[2] * otherMatrix.matrix[12] + matrix[6] * otherMatrix.matrix[13] + matrix[10] * otherMatrix.matrix[14] + matrix[14] * otherMatrix.matrix[15];
	temp.matrix[15] = matrix[3] * otherMatrix.matrix[12] + matrix[7] * otherMatrix.matrix[13] + matrix[11] * otherMatrix.matrix[14] + matrix[15] * otherMatrix.matrix[15];
	return temp;
}

template<class T>
inline Vec3<T> Matrix<T>::multiplyByVector(Vec3<T> vec)
{
	Vec3<T> temp;
	temp.x = vec.x * matrix[0] + vec.y * matrix[4] + vec.z * matrix[8];
	temp.y = vec.x * matrix[1] + vec.y * matrix[5] + vec.z * matrix[9];
	temp.z = vec.x * matrix[2] + vec.y * matrix[6] + vec.z * matrix[10];
	return temp;
}

template<class T>
inline Vec3<T> Matrix<T>::translateVector(Vec3<T> vec)
{
	Vec3<T> temp;
	temp.x = vec.x + matrix[12];
	temp.y = vec.y + matrix[13];
	temp.z = vec.z + matrix[14];
	return temp;
}

