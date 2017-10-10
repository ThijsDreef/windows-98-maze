#pragma once
template<class T>
class Vec4
{
public:
	T r, g, b, a;
	Vec4();
	Vec4(T r, T g, T b, T a);
	~Vec4();
	void product(Vec4<T> other);
	void plus(Vec4<T> other);
	void minus(Vec4<T> other);
	void divide(Vec4<T> other);
};

template<class T>
inline Vec4<T>::Vec4()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

template<class T>
inline Vec4<T>::Vec4(T r, T g, T b, T a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

template<class T>
inline Vec4<T>::~Vec4()
{
}

template<class T>
inline void Vec4<T>::product(Vec4<T> other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	a *= other.a
}

template<class T>
inline void Vec4<T>::plus(Vec4<T> other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
}

template<class T>
inline void Vec4<T>::minus(Vec4<T> other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
}

template<class T>
inline void Vec4<T>::divide(Vec4<T> other)
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
	a /= other.a;
}
