#pragma once
#ifndef BST_IMPL_H
#define BST_IMPL_H

#include <iostream>
#include <optional>
#include <stack>
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
        if (current != nullptr) {
            s.push(current);
            current = current->left;
        } else {
            current = current->right;
        }
        s.pop();

    }
    root = nullptr;
    count = 0;
}

template <typename TKey, typename TData>
size_t BinarySearchTree<TKey, TData>::size() const {
    return count;
}

template <typename TKey, typename TData>
TData BinarySearchTree<TKey, TData>::find(const TKey& key) {
    node* current = root;
    while (current != nullptr && current->key != key) {
        if (current->key < key)
            current = current->right;
        else
            current = current->left;
    }
    return current->data;
}

template <typename TKey, typename TData>
void BinarySearchTree<TKey, TData>::insert(const TKey& key, const TData& data) {
    node* newNode = new node { key, data, nullptr, nullptr };
    if (root == nullptr) {
        root = newNode;
        count++;
        return;
    } else if (root->key == newNode->key) {
        root->data = newNode->data;
        return;
    }
    node* current = root;
    node* parent = nullptr;
    
        
    while (current != nullptr) {
        parent = current;
        if (current->key < key)
            current = current->right;
        else
            current = current->left;
    }
    
    if (parent->key < key)
        parent->right = newNode;
    else
        parent->left = newNode;

    count++;
}

template <typename TKey, typename TData>
TKey BinarySearchTree<TKey, TData>::findNext(const TKey& key) {
    node* current = root;
    node* newKey = current;
    while (current != nullptr && current->key != key) {
        if (current->key < key)
            current = current->right;
        else {
            current = current->left;
            newKey = current;
        }
    }

    if (current->right == nullptr)
        return newKey->key;

    node* rightSon = current->right;
    if (rightSon->left == nullptr && rightSon->right == nullptr)
        return rightSon->key;
    current = rightSon->left;
    while (current->left != nullptr) {
        current = current->left;
    }

    return current->key;
}

template <typename TKey, typename TData>
void BinarySearchTree<TKey, TData>::remove(const TKey& key) {
    node* current = root;
    node* parent = current;
    while (current != nullptr && current->key != key) {
        parent = current;
        if (current->key < key)
            current = current->right;
        else
            current = current->left;
    }
    if (current->key == key) {
        if (current->right == nullptr && current->left == nullptr) {
            if (current == parent->right)
                parent->right = nullptr;
            else
                parent->left = nullptr;
            count--;
            delete current;
        }

        else if (!(current->right != nullptr && current->left != nullptr)) {
            if (current->right == nullptr) {
                if (current == parent->right)
                    parent->right = current->left;
                else
                    parent->left = current->left;
            } else {
                if (current == parent->right)
                    parent->right = current->right;
                else
                    parent->left = current->right;
            }
            count--;
            delete current;
        } else {
            node* rightSon = current->right;
            node* rsParent = current;
            while (rightSon->left != nullptr) {
                rsParent = rightSon;
                rightSon = rightSon->left;
            }

            if (rsParent != current) {
                rsParent->left = rightSon->right;
            }
            else {
                rsParent->right = rightSon->right;
            }

            current->key = rightSon->key;
            current->data = rightSon->data;
            count--;
            delete rightSon;
        }
    }
}

#endif // !BST_IMPL_H