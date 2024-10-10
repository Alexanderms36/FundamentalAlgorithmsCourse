#pragma once
#ifndef STACK_M_IMPL_H
#include "Stack_m.h"
#include <iostream>
#include <stdexcept>


template <typename T>
Stack_m<T>::Stack_m(size_t _capacity) : capacity(_capacity), count(0) {
	data = new T[capacity];
}

template <typename T>
Stack_m<T>::~Stack_m() {
	delete[] data;
}

template <typename T>
void Stack_m<T>::push(const T& new_top) {
	if (count == capacity)
		throw std::overflow_error("stack overflow");
	data[count++] = new_top;
}

template <typename T>
void Stack_m<T>::push(T&& new_top) {
	if (count == capacity)
		throw std::overflow_error("stack overflow");
	data[count++] = new_top;
}

template <typename T>
void Stack_m<T>::pop() {
	if (count == 0)
		throw std::underflow_error("no elements in the stack");
	--count;
}

template <typename T>
T& Stack_m<T>::top() {
	if (count == 0)
		throw std::underflow_error("no elements in the stack");
	return data[count - 1];
}

template <typename T>
const T& Stack_m<T>::top() const {
	if (count == 0)
		throw std::underflow_error("no elements in the stack");
	return data[count - 1];
}

template <typename T>
size_t Stack_m<T>::size() const {
	return count;
}

template <typename T>
Stack_m<T>::Stack_m(const Stack_m<T>& obj) : capacity(obj.capacity), count(obj.count) {
	data = new T[capacity];
	for (int i = 0; i < count; ++i)
		data[i] = obj.data[i];
}

template <typename T>
Stack_m<T>::Stack_m(Stack_m<T>&& obj) : data(obj.data), capacity(obj.capacity), count(obj.count) {
	obj.data = nullptr;
	obj.capacity = 0;
	obj.count = 0;
}

template <typename T>
Stack_m<T>& Stack_m<T>::operator=(const Stack_m<T>& obj) {
	if (this != &obj) {
		delete[] data;
		capacity = obj.capacity;
		count = obj.count;
		data = new T[capacity];
		for (size_t i = 0; i < count; ++i)
			data[i] = obj.data[i];
	}
	return *this;
}

template <typename T>
Stack_m<T>& Stack_m<T>::operator=(Stack_m<T>&& obj) {
	if (this != &obj) {
		delete[] data;
		capacity = obj.capacity;
		count = obj.count;
		obj.data = nullptr;
		obj.capacity = 0;
		obj.count = 0;
	}
	return *this;
}
#endif // !STACK_M_IMPL_H
