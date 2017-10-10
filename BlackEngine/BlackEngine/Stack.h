#pragma once
#include <iostream>
template <class T>
class Stack
{
private:
	int maxSize = 0;
	int size = 0;
	T * stack = new T[0];
	void resize(); 
public:
	Stack(int maxsize);
	Stack();
	~Stack();
	void push(T item);
	int capacity();
	T pop();
	T peek();
};

template<class T>
inline void Stack<T>::resize()
{
	T * temp = new T[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		temp[i] = stack[i];
	}
	delete[] stack;
	stack = temp;
}

template<class T>
inline Stack<T>::Stack(int maxsize)
{
	maxSize = maxsize;
	stack = new T[maxSize];
}

template<class T>
inline Stack<T>::Stack()
{
	maxSize = 10;
	stack = new T[maxSize];
}

template<class T>
inline Stack<T>::~Stack()
{
	delete[] stack;
}

template<class T>
inline void Stack<T>::push(T item)
{
	size++;
	if (size >= maxSize -1)
	{
		maxSize = size;
		maxSize++;
		resize();
	}
	stack[size] = item;
}

template<class T>
inline int Stack<T>::capacity()
{
	return size;
}



template<class T>
inline T Stack<T>::pop()
{
	T objectToReturn = stack[size];
	stack[size] = 0;
	if (size != 0)
	{
		size--;
	}
	else
	{
		return 0;
	}
	return objectToReturn;
}

template<class T>
inline T Stack<T>::peek()
{
	return stack[size];
}
