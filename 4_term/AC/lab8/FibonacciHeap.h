#ifndef LAB8_FIBONACCI_HEAP_H
#define LAB8_FIBONACCI_HEAP_H

#include "FileSystem.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

const int INF = 10e6;

class Node{
public:
    int value;
    Node* parent;
    Node* left;
    Node* right;
    Node* child;
    bool mark{};
    int degree{};
    Node();
    explicit Node(int newValue);
    ~Node() = default;
    void print (int countTabs, Node* head) const;
    void clear (Node* head);
    void insertBetween (Node* _left, Node* _right);
    void extractBetween();
    int values();
};

class FibonacciHeap {
private:
    Node* min;
    int countNodes{};
    void cut (Node* son, Node* parent);
    void cascadingCut(Node* node);
    void consolidate ();
    void link (Node* lower, Node* higher);
    void unionHeaps (FibonacciHeap* first, FibonacciHeap* second);
public:
    FibonacciHeap();
    explicit FibonacciHeap(int value);
    ~FibonacciHeap();
    void print () const;
    void extractMin ();
    void decreaseKey(Node* node, int newValue);
    void deleteNode (Node* node);
    Node* insert(int value);
    Node* insert(Node* node);
    bool empty();
    Node* minimum();
};

#endif //LAB8_FIBONACCI_HEAP_H
