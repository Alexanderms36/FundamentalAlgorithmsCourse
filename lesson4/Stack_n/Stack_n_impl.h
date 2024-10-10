#pragma once
#ifndef STACK_N_IMPL_H
#define STACK_N_IMPL_H
#include <iostream>
#include <stdexcept>


template <typename T>
Stack_n<T>::Stack_n() : node(nullptr), count(0) {}

template <typename T>
Stack_n<T>::~Stack_n() {
	while (count > 0)
		pop();
}

template <typename T>
void Stack_n<T>::push(T&& new_top) {
	Node<T>* new_node = new Node<T>{ new_top, node };
	node = new_node;
	count++;
}

template <typename T>
void Stack_n<T>::push(const T& new_top) {
	node = new Node<T>{ new_top, node };
	++count;
}

template <typename T>
void Stack_n<T>::pop() {
	if (count == 0)
		throw std::underflow_error("stack is empty");
	Node<T>* tmp = node;
	node = node->next;
	delete tmp;
	count--;
}

template <typename T>
T& Stack_n<T>::top() {
	if (count == 0)
		throw std::underflow_error("stack is empty");
	return node->data;
}

template <typename T>
const T& Stack_n<T>::top() const {
	if (count == 0)
		throw std::underflow_error("stack is empty");
	return node->data;
}

template <typename T>
size_t Stack_n<T>::size() const {
	return count;
}

template <typename T>
Stack_n<T>::Stack_n(const Stack_n<T>& obj) : node(nullptr), count(0) {
	if (obj.node) {
		Node<T>* current = obj.node;
		Node<T>* last = nullptr;
		while (current) {
			Node<T>* new_node = new Node<T>{ current->data, nullptr };
			if (!node) {
				node = new_node;
			} else {
				last->next = new_node;
			}
			last = new_node;
			current = current->next;
		}
		count = obj.count;
	}
}

template <typename T>
Stack_n<T>::Stack_n(Stack_n<T>&& obj) : node(obj.node), count(obj.count) {
	obj.node = nullptr;
	obj.count = 0;
}

template <typename T>
Stack_n<T>& Stack_n<T>::operator=(const Stack_n<T>& obj) {
	if (this != &obj) {
		Node<T>* current = obj.node;
		Node<T>* last = nullptr;

		while (current) {
			Node<T>* new_node = new Node<T>{ current->data, nullptr };
			if (!node) {
				node = new_node;
			} else {
				last->next = new_node;
			}
			last = new_node;
			current = current->next;
		}
		count = obj.count;
	}
	return *this;
}

template <typename T>
Stack_n<T>& Stack_n<T>::operator=(Stack_n<T>&& obj) {
	if (this != &obj) {
		while (count > 0) {
			pop();
		}

		node = obj.node;
		count = obj.count;

		obj.node = nullptr;
		obj.count = 0;
	}
	return *this;
}
#endif
