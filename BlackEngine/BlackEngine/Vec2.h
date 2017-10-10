#pragma once
#include <iostream>
template<class T>
class Vec2
{
public:
	T x, y;
	Vec2();
	Vec2(T x, T y);
	~Vec2();
	void product(Vec2<T> other);
	void plus(Vec2<T> other);
	void minus(Vec2<T> other);
	void divide(Vec2<T> other);
	void debug();
};

template<class T>
inline Vec2<T>::Vec2()
{
	x = 0;
	y = 0;
}

template<class T>
inline Vec2<T>::Vec2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
inline Vec2<T>::~Vec2()
{
}

template<class T>
inline void Vec2<T>::product(Vec2<T> other)
{
	x *= other.x;
	y *= other.y;
}

template<class T>
inline void Vec2<T>::plus(Vec2<T> other)
{
	x += other.x;
	y += other.y;
}

template<class T>
inline void Vec2<T>::minus(Vec2<T> other)
{
	x -= other.x;
	y -= other.y;
}

template<class T>
inline void Vec2<T>::divide(Vec2<T> other)
{
	x /= other.x;
	y /= other.y;
}

template<class T>
inline void Vec2<T>::debug()
{
	std::cout << x << y << std::endl;
}
