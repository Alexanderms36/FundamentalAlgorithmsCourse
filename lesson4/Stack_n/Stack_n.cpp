#pragma once
#ifndef STACK_N_H // stack implementation using nodes
#define STACK_N_H


template <typename T>
class Stack_n {
private:
	template <typename T>
	struct Node {
		T data;
		Node* next;
	};

	Node<T>* node;
	size_t count;

public:
	Stack_n();
	~Stack_n();
	void push(const T& new_top);
	void push(T&& new_top);
	void pop();
	T& top();
	const T& top() const;
	size_t size() const;
	Stack_n(const Stack_n<T>& obj);
	Stack_n(Stack_n<T>&& obj);
	Stack_n<T>& operator=(const Stack_n<T>& obj);
	Stack_n<T>& operator=(Stack_n<T>&& obj);
};
#include "Stack_n_impl.h"
#endif