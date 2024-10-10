#pragma once //Stack implementation using an array
#ifndef STACK_M_H
#define STACK_M_H
template <typename T>
class Stack_m {
	T* data;
	size_t capacity, count;

public:
	Stack_m(size_t _capacity = 50000);
	~Stack_m(); //деструктор
	void push(const T& new_top);
	void push(T&& new_top);
	void pop();
	T& top();
	const T& top() const;
	size_t size() const;
	Stack_m(const Stack_m<T>& obj); //копирование
	Stack_m(Stack_m<T>&& obj); //перемещение
	Stack_m<T>& operator=(const Stack_m<T>& obj); //оператор копирования
	Stack_m<T>& operator=(Stack_m<T>&& obj); //оператор перемещения
};
#include "Stack_m_impl.h"
#endif