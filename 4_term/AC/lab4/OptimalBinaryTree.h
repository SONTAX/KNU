#ifndef LAB4_OPTIMALBINARYTREE_H
#define LAB4_OPTIMALBINARYTREE_H

#include "FileSystem.h"
#include <vector>
#include <algorithm>

class Node {
public:
   int value;
   double probability;
   bool key;
   Node* parent;
   Node* left;
   Node* right;
   Node();
   explicit Node(int value, double probability, bool key);
   ~Node() = default;
   void output(Node *node, int space) const;
};

class OptimalBinaryTree {
private:
    Node* root;
    int countKeys;
    double* keys;
    double* fictitiousKeys;
    double** expectedValue;
    int** roots;
    void GenerateTables();
    Node* GenerateTree(int i, int j, Node* parent);
public:
    OptimalBinaryTree(const int count, const double* newKeys, const double* newFictitiousKeys);
    ~OptimalBinaryTree();
    void output() const;
};

#endif //LAB4_OPTIMALBINARYTREE_H
