#ifndef LAB3_SPLAYTREE_H
#define LAB3_SPLAYTREE_H

#include "FileSystem.h"
#include <vector>
#include <algorithm>

class Node {
public:
    int value;
    Node* parent;
    Node* left;
    Node* right;
    Node();
    explicit Node(int value);
    ~Node() = default;
    void output(Node *node, int space) const;
};

class SplayTree {
    Node* root;
    void splay(Node* toSplay, Node* rootSplay);
    void zig(Node* toSplay, bool leftSide);
    void zig_zig(Node* toSplay, bool leftSide);
    void zig_zag(Node* toSplay, bool leftSide);
    void merge(Node* rootLeft, Node* rootRight);
    void split(const int& t);
    Node* get(Node* node, const int& t);
public:
    SplayTree();
    ~SplayTree() = default;
    void insert(int& t);
    void erase(int& t);
    void output() const;
};


#endif //LAB3_SPLAYTREE_H
