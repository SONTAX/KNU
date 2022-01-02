#ifndef LAB6_BPLUSTREE_H
#define LAB6_BPLUSTREE_H

#include "FileSystem.h"
#include <vector>

class Element{
public:
    int key{};
    string data;
    Element(int key, string data);
};

class Node{
public:
    std::vector<Element> elements;
    std::vector<Node*> children;
    Node* parent;
    Node* leftSibling;
    Node* rightSibling;
    bool isLeaf{};
    Node();
    Node(const bool& isLeaf, const vector<Element>& elements, const vector<Node*>& children);
    bool contain(const int key) const;
    int findPosition(const int key) const;
    int findPositionInChildrenByNode(const Node* node) const;
    void free(Node* node);
    void print(int spaces) const;
};

class BPlusTree {
private:
    int power{};
    Node* root;
    Node* moveHalfNodeToNewOne(Node* toSplit);
    Node* findLeaf(Node* node, int toFind);
    Element getMin(Node* node);
    Element getSuccessor(Node* node, int key);
    void borrowElementInternal(Node* toUpdate, Node* sibling);
    void updateKeys(Node* toUpdate, const int key);
    void split(Node* toSplit);
    void mergeLeaves(Node* left, Node* right);
    void erase(Node* toDelete, int key);
    void mergeWithParent(Node* toUpdate, Node* sibling);
public:
    explicit BPlusTree(const int& power);
    ~BPlusTree();
    void erase(int key);
    void insert(const int& key, const string& data);
    void print();
    string search(int key);
};


#endif //LAB6_BPLUSTREE_H
