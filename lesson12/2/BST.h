#pragma once
#ifndef BST_H
#define BST_H
#include <optional>

using namespace std;

template <typename TKey, typename TData>
class BinarySearchTree {
private:
	struct node {
		TKey key;
		TData data;
		node *left, *right;
	} *root = nullptr;
	size_t count = 0;
public:
	BinarySearchTree();
	~BinarySearchTree();

	size_t size() const;
	TData find(const TKey& key);
	void insert(const TKey& key, const TData& data);
	TKey findNext(const TKey& key);
	void remove(const TKey& key);
};
#include "BST_impl.h"
#endif // !BST_H