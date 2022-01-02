#include "FibonacciHeap.h"

Node::Node() {
    value = 0;
    mark = false;
    parent = child = nullptr;
    left = right = this;
    degree = 0;
}

Node::Node(int newValue) {
    value = newValue;
    mark = false;
    parent = child = nullptr;
    left = right = this;
    degree = 0;
}

void Node::print(int countTabs, Node* head) const {
    for (int i = 0; i < countTabs; i++) {
        std::cout << '\t';
    }
    std::cout << value << ":" << degree << ":" << mark;
    if (child != nullptr) {
        std::cout << std::endl;
        child->print(countTabs + 1, child);
    }
    if (left != head) {
        std::cout << std::endl;
        left->print(countTabs, head);
    }
}

void Node::clear(Node* head) {
    if (this != nullptr) {
        if (child != nullptr) {
            child->clear(child);
        }
        if (left != head) {
            left->clear(head);
        }
        delete this;
    }
}

void Node::insertBetween(Node* _left, Node* _right) {
    _left->right = _right->left = this;
    this->right  = _right;
    this->left   = _left;
}

void Node::extractBetween() {
    left->right = right;
    right->left = left;
    left = right = nullptr;
}

int Node::values() {
    return value;
}

void FibonacciHeap::cut(Node* son, Node* parent) {
    if (son == son->right) {
        parent->child = nullptr;
    } else {
        parent->child = son->right;
    }
    parent->degree--;
    son->parent = nullptr;
    son->extractBetween();
    son->insertBetween(min, min->right);
    son->mark = false;
}

void FibonacciHeap::cascadingCut(Node* node) {
    Node* parent = node->parent;
    if (parent != nullptr) {
        if (node->mark == false) {
            node->mark = true;
        } else {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

void FibonacciHeap::consolidate() {
    int size = round(log(countNodes))+2;
    auto array = new Node* [size];
    for (int i = 0; i < size; i++) {
        array[i] = nullptr;
    }
    map< Node* , bool> dict;
    Node* temp = min, *rightSibling = nullptr;
    do {
        dict[temp] = true;
        rightSibling = temp->right;
        Node* x = temp;
        int degree = x->degree;
        while (array[degree] != nullptr) {
            Node* y = array[degree];
            if (x->value > y->value) {
                auto z = x;
                x = y;
                y = z;
            }
            link(y, x);
            array[degree] = nullptr;
            degree++;
        }
        array[degree] = x;
        temp = rightSibling;
    } while (dict[temp] == false);
    for (int i = 0; i < size; i++) {
        if (array[i] != nullptr) {
            if (min->value > array[i]->value) {
                min = array[i];
            }
        }
    }
}

void FibonacciHeap::link(Node* lower, Node* higher) {
    lower->extractBetween();
    if (higher->child == nullptr) {
        higher->child = lower;
        lower->right = lower->left = lower;
    } else {
        lower->insertBetween(higher->child, higher->child->right);
    }
    lower->parent = higher;
    higher->degree++;
    lower->mark = false;
}

void FibonacciHeap::unionHeaps(FibonacciHeap* first, FibonacciHeap* second) {
    if (first->min == nullptr && second->min == nullptr) {
        return;
    }
    if (first->min == nullptr) {
        min = second->min;
        countNodes = second->countNodes;
        return;
    }
    if (second->min == nullptr) {
        min = first->min;
        countNodes = first->countNodes;
        return;
    }
    min = std::min(first->min, second->min);
    Node* rightSiblingFirst = first->min->right;
    Node* leftSiblingSecond = second->min->left;
    first->min->right = second->min;
    second->min->left = first->min;
    rightSiblingFirst->left  = leftSiblingSecond;
    leftSiblingSecond->right = rightSiblingFirst;
    countNodes = first->countNodes + second->countNodes;
    second->min = nullptr;
}

FibonacciHeap::FibonacciHeap() {
    min = nullptr;
    countNodes = 0;
}

FibonacciHeap::FibonacciHeap(int value) {
    min = new Node(value);
    countNodes = 0;
}

FibonacciHeap::~FibonacciHeap() {
    if (min != nullptr) {
        min->clear(min);
    }
}

void FibonacciHeap::print() const {
    if (min != nullptr) {
        min->print(0, min);
    } else {
        std::cout << "Heap is empty";
    }
    std::cout << "\nCount nodes = " << countNodes << '\n';
}

void FibonacciHeap::extractMin() {
    Node* head = min;
    if (head != nullptr) {
        if (head->child != nullptr) {
            Node* temp = head->child, *rightSibling;
            do {
                rightSibling = temp->right;
                temp->parent = nullptr;
                temp->extractBetween();
                temp->insertBetween(min->left, min);
                temp = rightSibling;

            } while (temp->right != min);
        }
        if (head == head->right) {
            min = nullptr;
        } else {
            min = head->right;
            head->extractBetween();
            consolidate();
        }
        countNodes--;
    }
    head->child = nullptr;
    head->clear(head);
}

void FibonacciHeap::decreaseKey(Node *node, int newValue) {
    if (newValue > node->value) {
        return;
    }
    node->value = newValue;
    Node* parent = node->parent;
    if (parent != nullptr && node->value < parent->value) {
        cut(node, parent);
        cascadingCut(parent);
    }
    if (node->value < min->value) {
        min = node;
    }
}

void FibonacciHeap::deleteNode(Node* node) {
    decreaseKey(node, -INF);
    extractMin();
}

Node* FibonacciHeap::insert(int value) {
    auto node = new Node(value);
    return insert(node);
}

Node* FibonacciHeap::insert(Node* node) {
    countNodes++;
    if (min == nullptr) {
        min = node;
        return node;
    }
    if (min->left == min) {
        min->left   = node;
        min->right  = node;
        node->right = min;
        node->left  = min;

    } else {
        Node* leftSibling = min->left;
        leftSibling->right = node;
        min->left = node;
        node->right = min;
        node->left = leftSibling;
    }
    if (node->value < min->value) {
        min = node;
    }
    return node;
}

bool FibonacciHeap::empty() {
    return min == nullptr;
}

Node* FibonacciHeap::minimum() {
    return min;
}