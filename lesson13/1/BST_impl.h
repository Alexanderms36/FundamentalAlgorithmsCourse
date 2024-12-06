#pragma once
#ifndef BST_IMPL_H
#define BST_IMPL_H

#include <iostream>
#include <optional>
#include <stack>
#include <queue>
#include <optional>
#include "BST.h"

using namespace std;

template <typename TKey, typename TData>
BinarySearchTree<TKey, TData>::BinarySearchTree() {
    root = nullptr;
    count = 0;
}

template <typename TKey, typename TData>
BinarySearchTree<TKey, TData>::~BinarySearchTree() {
    if (root == nullptr) return;
    stack<node*> s;
    node* current = root;

    while (s.size() || current) {
        if (current) {
            s.push(current);
            current = current->left;
        } else {
            current = current->right;
            delete s.top();
        }
        s.pop();

    }
}

template <typename TKey, typename TData>
typename BinarySearchTree<TKey, TData>::node** BinarySearchTree<TKey, TData>::_find(const TKey& k) const {
    node** p = (node**)&root;
    while (*p && (*p)->key != k)
        p = (*p)->key < k ? &((*p)->right) : &((*p)->left);
    return p;
}

template <typename TKey, typename TData>
size_t BinarySearchTree<TKey, TData>::size() const {
    return count;
}

template <typename TKey, typename TData>
optional<reference_wrapper<TData>> BinarySearchTree<TKey, TData>::find(const TKey& k) const {
    auto p = _find(k);
    if (*p) return (*p)->data;
    return nullopt;
}

template <typename TKey, typename TData>
void BinarySearchTree<TKey, TData>::insert(const TKey& k, const TData& d) {
    auto p = _find(k);
    if (*p) (*p)->data = d;
    else {
        *p = new node{ k, d };
        ++count;
    }
}

template <typename TKey, typename TData>
optional<TKey> BinarySearchTree<TKey, TData>::findnext(const TKey& key) const {
    node** p = (node**)&root;
    node** lastleft = nullptr;
    while (*p)
        p = key < (*p)->key ? (lastleft = p, &((*p)->left)) : &((*p)->right);
    return lastleft ? optional<TKey>((*lastleft)->key) : nullopt;
}

template <typename TKey, typename TData>
void BinarySearchTree<TKey, TData>::remove(const TKey& k) {
    node** p = _find(k);
    if (*p == nullptr) return;
    --count;
    if (!(*p)->left || !(*p)->right) {
        auto tmp = *p;
        *p = tmp->left ? tmp->left : tmp->right;
        delete tmp;
    } else {
        auto nxt = &(*p)->right;
        while ((*nxt)->left) nxt = &(*nxt)->left;
        (*p)->key = (*nxt)->key;
        (*p)->data = (*nxt)->data;
        node* tmp = *nxt;
        *nxt = tmp->right;
        delete tmp;
    }
}

template <typename TKey, typename TData>
size_t BinarySearchTree<TKey, TData>::_height(node* node) const {
    if (node == nullptr) {
        return 0;
    }
    size_t leftH = _height(node->left);
    size_t rightH = _height(node->right);
    return max(leftH, rightH) + 1;
}

template <typename TKey, typename TData>
size_t BinarySearchTree<TKey, TData>::height() const {
    return _height(root);
}

template <typename TKey, typename TData>
size_t BinarySearchTree<TKey, TData>::height2() const {
    if (root == nullptr) return 0;
    
    queue<node*> q;
    q.push(root);
    size_t height = 0;
    node* curr;

    while (!q.empty()) {
        size_t qsize = q.size();
        for (size_t i = 0; i < qsize; i++) {
            curr = q.front();
            q.pop();
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        height++;
    }
    
    return height;
}

template <typename TKey, typename TData>
void BinarySearchTree<TKey, TData>::_width(node* n, int x, int& minX, int& maxX) const {
    if (n == nullptr) return;

    minX = min(minX, x);
    maxX = max(maxX, x);

    _width(n->left, x - 1, minX, maxX); 
    _width(n->right, x + 1, minX, maxX);
}

template <typename TKey, typename TData>
int BinarySearchTree<TKey, TData>::width() const {
    if (root == nullptr) return 0;

    int minX = 0, maxX = 0;
    _width(root, 0, minX, maxX);
    return maxX - minX + 1;
}

template <typename TKey, typename TData>
bool BinarySearchTree<TKey, TData>::_secondaryKey(node* r, int minData, int maxData) const {
    if (r == nullptr) {
        return true;
    }

    if (r->data <= minData || r->data >= maxData) {
        return false;
    }

    return _secondaryKey(r->left, minData, r->data) && _secondaryKey(r->right, r->data, maxData);
}

template <typename TKey, typename TData>
bool BinarySearchTree<TKey, TData>::is_bst_by_secondary_key() const {
    return _secondaryKey(root, INT_MIN, INT_MAX);
}

#endif // !BST_IMPL_H