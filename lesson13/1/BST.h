#pragma once
#ifndef BST_H
#define BST_H
#include <optional>
#include <vector>
#include <functional>

using namespace std;

template <typename TKey, typename TData>
class BinarySearchTree {
private:
	struct node {
		TKey key;
		TData data;
		node* left = nullptr, * right = nullptr;
	} *root = nullptr;
	size_t count = 0;
	node** _find(const TKey& key) const;
	size_t _height(node* r) const;
	void _width(node* n, int x, int& minX, int& maxX) const;

	bool _secondaryKey(node* r, int minData, int maxData) const;

public:
	BinarySearchTree();
	~BinarySearchTree();
	optional<reference_wrapper<TData>> find(const TKey& key) const;
	void insert(const TKey& k, const TData& d);
	optional<TKey> findnext(const TKey& key) const;
	optional<TKey> findprev(const TKey& key) const;
	void remove(const TKey& key);
	void visit(function<void(const TKey&, const TData&)> worker) const;
	size_t height() const;
	size_t height2() const;
	vector<pair<TKey, TData>> dump() const;
	bool is_bst_by_secondary_key() const;
	int width() const;
	
	size_t size() const;
};
#include "BST_impl.h"
#endif // !BST_H
