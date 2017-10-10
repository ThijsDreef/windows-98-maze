#pragma once
#include <iostream>
template<class T>
class Vec3
{
public:
	T x, y, z;
	Vec3();
	Vec3(T x, T y, T z);
	~Vec3();
	Vec3<T> product(Vec3<T> other);
	Vec3<T> plus(Vec3<T> other);
	Vec3<T> minus(Vec3<T> other);
	Vec3<T> divide(Vec3<T> other);
	Vec3<T> product(T other);
	Vec3<T> plus(T other);
	Vec3<T> minus(T other);
	Vec3<T> divide(T other);
	void reset();
	void debug();
};

template<class T>
inline Vec3<T>::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

template<class T>
inline Vec3<T>::Vec3(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T>
inline Vec3<T>::~Vec3()
{
}

template<class T>
inline Vec3<T> Vec3<T>::product(Vec3<T> other)
{
	return Vec3<T>(x * other.x, y * other.y, z * other.z);
}

template<class T>
inline Vec3<T> Vec3<T>::plus(Vec3<T> other)
{
	return Vec3<T>(x + other.x, y + other.y, z + other.z);
}

template<class T>
inline Vec3<T> Vec3<T>::minus(Vec3<T> other)
{
	return Vec3<T>(x - other.x, y - other.y, z - other.z);

}

template<class T>
inline Vec3<T> Vec3<T>::divide(Vec3<T> other)
{
	return Vec3<T>(x / other.x, y / other.y, z / other.z);
}

template<class T>
inline Vec3<T> Vec3<T>::product(T other)
{
	return Vec3<T>(x * other, y * other, z * other);
}

template<class T>
inline Vec3<T> Vec3<T>::plus(T other)
{
	return Vec3<T>(x + other, y + other, z + other);
}

template<class T>
inline Vec3<T> Vec3<T>::minus(T other)
{
	return Vec3<T>(x - other, y - other, z - other);
}

template<class T>
inline Vec3<T> Vec3<T>::divide(T other)
{
	return Vec3<T>(x / other, y / other, z / other);
}

template<class T>
inline void Vec3<T>::reset()
{
	x = 0;
	y = 0;
	z = 0;
}

template<class T>
inline void Vec3<T>::debug()
{
	std::cout << "x " << x << " y " << y << " z " << z << std::endl;
}
