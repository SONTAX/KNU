#ifndef LAB7_BINOMIAL_HEAP_H
#define LAB7_BINOMIAL_HEAP_H

#include "FileSystem.h"

const int INF = 10e6;

class Node{
public:Node* parent;
    Node* sibling;
    Node* child;
    int value;
    int degree{};
    Node();
    explicit Node(int newValue);
    void print(int countTabs) const;
    void link (Node* other);
    /*friend std::ostream& operator<< (std::ostream &out, const Node &node){
        out << node.value;
        return out;
    }
    friend BinomialHeap;*/
};

class BinomialHeap {
public:
    Node* head;
    BinomialHeap();
    explicit BinomialHeap(int newValue);
    ~BinomialHeap() = default;
    void print() const;
    void merge(BinomialHeap *first, BinomialHeap *second);
    void unionHeaps (BinomialHeap* first, BinomialHeap* second);
    void insert (int value);
    void extractMin ();
    void decreaseKey(Node* node, int newValue);
    void erase (Node* node);
    Node* minNode() const;
    Node* prevMinNode() const;
};

#endif //LAB7_BINOMIAL_HEAP_H
