#include "BinomialHeap.h"

Node::Node() {
    parent = sibling = child = nullptr;
    value = degree = 0;
}

Node::Node(int newValue) {
    parent = sibling = child = nullptr;
    degree = 0;
    value = newValue;
}

void Node::print(int countTabs) const {
    for (int i = 0; i < countTabs; i++) {
        std::cout << '\t';
    }
    std::cout << value << ":" << degree;
    if (child != nullptr) {
        std::cout << std::endl;
        child->print(countTabs + 1);
    }
    if (sibling != nullptr) {
        std::cout << std::endl;
        sibling->print(countTabs);
    }
    std::cout << std::endl;
}

void Node::link(Node* other) {
    this->parent = other;
    this->sibling = other->child;
    other->child = this;
    other->degree++;
}

BinomialHeap::BinomialHeap() {
    head = nullptr;
}

BinomialHeap::BinomialHeap(int newValue) {
    head = new Node(newValue);
}

void BinomialHeap::print() const {
    head->print(0);
}

void BinomialHeap::merge(BinomialHeap *first, BinomialHeap *second) {
    if (first->head == nullptr) {
        head = second->head;
        return;
    }
    if (second->head == nullptr) {
        head = first->head;
        return;
    }
    Node* firstTemp = first->head;
    Node* secondTemp = second->head;
    if (firstTemp->degree <= secondTemp->degree) {
        head       = firstTemp;
        firstTemp  = firstTemp->sibling;
    } else {
        head       = secondTemp;
        secondTemp = secondTemp->sibling;
    }
    Node* temp = head;
    while (firstTemp != nullptr && secondTemp != nullptr) {
        if (firstTemp->degree < secondTemp->degree) {
            temp->sibling = firstTemp;
            temp = temp->sibling;
            firstTemp = firstTemp->sibling;
        } else {
            temp->sibling = secondTemp;
            temp          = temp->sibling;
            secondTemp    = secondTemp->sibling;
        }
    }
    while (firstTemp != nullptr) {
        temp->sibling = firstTemp;
        temp          = temp->sibling;
        firstTemp     = firstTemp->sibling;
    }
    while (secondTemp != nullptr) {
        temp->sibling = secondTemp;
        temp          = temp->sibling;
        secondTemp    = secondTemp->sibling;
    }
}

void BinomialHeap::unionHeaps(BinomialHeap *first, BinomialHeap *second) {
    merge(first, second);
    if (head == nullptr) {
        return;
    }
    Node* prevX = nullptr;
    Node* X = head;
    Node*nextX = X->sibling;
    while (nextX != nullptr) {
        if (X->degree != nextX->degree || (nextX->sibling != nullptr && nextX->sibling->degree == X->degree)) {
            prevX = X;
            X     = nextX;
        } else if (X->value <= nextX->value) {
            X->sibling = nextX->sibling;
            nextX->link(X);
        } else {
            if (prevX == nullptr) {
                head = nextX;
            } else {
                prevX->sibling = nextX;
            }
            X->link(nextX);
            X = nextX;
        }
        nextX = X->sibling;
    }
}

void BinomialHeap::insert(int value) {
    auto tree = new BinomialHeap(value);
    unionHeaps(this, tree);
    delete tree;
}

void BinomialHeap::extractMin() {
    if (head == nullptr) {
        return;
    }
    Node* min = minNode();
    Node* prevMin = prevMinNode();
    if (prevMin != nullptr) {
        prevMin->sibling = min->sibling;
    } else {
        head = min->sibling;
    }
    if (min->child == nullptr) {
        return;
    }
    Node* first = nullptr;
    Node* second = min->child;
    Node* third = second->sibling;
    while (second != nullptr) {
        second->parent = nullptr;
        second->sibling = first;
        first = second;
        second = third;
        third = third == nullptr ? nullptr : third->sibling;
    }
    BinomialHeap tree;
    tree.head = first;
    unionHeaps(this, &tree);
    delete min;
}

void BinomialHeap::decreaseKey(Node *node, int newValue) {
    if (newValue > node->value){
        std::cout << "New value is more than old one\n";
        return;
    }
    node->value = newValue;
    Node* temp = node;
    Node* parent = node->parent;
    while (parent != nullptr && parent->value > temp->value) {
        int tempValue = parent->value;
        parent->value = temp->value;
        temp->value = tempValue;
        temp = parent;
        parent = parent->parent;
    }
}

void BinomialHeap::erase(Node *node) {
    decreaseKey(node, -INF);
    extractMin();
}

Node * BinomialHeap::minNode() const {
    Node* minimal = head;
    Node* temp    = head->sibling;
    while (temp != nullptr) {
        if (temp->value < minimal->value) {
            minimal = temp;
        }
        temp = temp->sibling;
    }
    return minimal;
}

Node * BinomialHeap::prevMinNode() const {
    Node* tempPrev = head;
    Node* prev = nullptr;
    Node* minimal = head;
    Node* temp = head->sibling;
    while (temp != nullptr) {
        if (temp->value < minimal->value) {
            prev    = tempPrev;
            minimal = temp;
        }
        tempPrev = tempPrev != nullptr ? tempPrev->sibling : head;
        temp = temp->sibling;
    }
    return prev;
}