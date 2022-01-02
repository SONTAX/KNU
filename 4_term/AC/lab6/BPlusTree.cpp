#include "BPlusTree.h"

Element::Element(int key, string data) {
    this->key = key;
    this->data = data;
}

Node::Node() {
    isLeaf = false;
    children.clear();
    elements.clear();
}

Node::Node(const bool &isLeaf, const vector<Element> &elements, const vector<Node *> &children) {
    parent = leftSibling = rightSibling = nullptr;
    this->isLeaf = isLeaf;
    this->elements = elements;
    this->children = children;
}

bool Node::contain(const int key) const {
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].key == key) {
            return true;
        }
    }
    return false;
}

int Node::findPosition(const int key) const {
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].key == key) {
            return i;
        }
    }
    return -1;
}

int Node::findPositionInChildrenByNode(const Node *node) const {
    for (int i = 0; i < this->children.size(); i++) {
        if (this->children[i] == node) {
            return i;
        }
    }
    return -1;
}

void Node::free(Node *node) {
    if (node == nullptr) {
        return;
    }
    for (auto i : node->children) {
        free(i);
    }
    delete node;
}

void Node::print(int spaces) const {
    if (this == nullptr) {
        return;
    }
    if (children[elements.size()] != nullptr) {
        children[elements.size()]->print(spaces + 1);
    } else {
        for (int j = 0; j < spaces+1; j++) {
            std::cout << "\t";
        }
        std::cout << "null\n";
    }
    for (int i = elements.size() - 1; i >= 0; i--) {
        for (int j = 0; j < spaces; j++) {
            std::cout << "\t";
        }
        std::cout << elements[i].key << ":" << elements[i].data << std::endl;
        if (children[i] != nullptr) {
            children[i]->print(spaces + 1);
        } else {
            for (int j = 0; j < spaces+1; j++) {
                std::cout << "\t";
            }
            std::cout << "null\n";
        }
    }
}

Node* BPlusTree::moveHalfNodeToNewOne(Node *toSplit) {
    std::vector<Element> elementsSplit;
    std::vector<Node*> childSplit;
    Element midEl = toSplit->elements[power];
    for (int i = 0; i < power - 1; i++) {
        elementsSplit.emplace_back(toSplit->elements[i + power + 1]);
        childSplit.emplace_back(toSplit->children[i + power + 1]);
    }
    childSplit.emplace_back(toSplit->children[power * 2]);
    if (toSplit->isLeaf) {
        elementsSplit.emplace(elementsSplit.begin(), midEl);
        childSplit.emplace(childSplit.begin(), nullptr);
    }
    Node* afterSplit = new Node(toSplit->isLeaf, elementsSplit, childSplit);
    for (int i = 0; i < afterSplit->children.size(); i++) {
        if (afterSplit->children[i] != nullptr) {
            afterSplit->children[i]->parent = afterSplit;
        }
    }
    for (int i = 0; i < power; i++) {
        toSplit->elements.pop_back();
        toSplit->children.pop_back();
    }
    afterSplit->rightSibling = toSplit->rightSibling;
    if (afterSplit->rightSibling != nullptr) {
        afterSplit->rightSibling->leftSibling = afterSplit;
    }
    toSplit->rightSibling = afterSplit;
    afterSplit->leftSibling = toSplit;
    return afterSplit;
}

Node* BPlusTree::findLeaf(Node *node, int toFind)  {
    if (node->isLeaf) {
        return node;
    }
    for (int i = 0; i < node->elements.size(); i++) {
        if (toFind < node->elements[i].key) {
            return findLeaf(node->children[i], toFind);
        }
    }
    return findLeaf(node->children[node->children.size() - 1], toFind);
}

Element BPlusTree::getMin(Node *node) {
    if (node == nullptr) {
        return {0, 0};
    }
    if (node->isLeaf) {
        return node->elements[0];
    }
    return getMin(node->children[0]);
}

Element BPlusTree::getSuccessor(Node *node, int key) {
    int pos = node->findPosition(key);
    return getMin(node->children[pos + 1]);
}

void BPlusTree::borrowElementInternal(Node *toUpdate, Node *sibling) {
    Node* parent = toUpdate->parent;
    if (sibling == toUpdate->leftSibling) {
        int pos = 0;
        for (int i = 0; i < parent->children.size(); i++) {
            if (parent->children[i] == toUpdate) {
                pos = i;
            }
        }
        toUpdate->elements.template emplace(toUpdate->elements.begin(), parent->elements[pos - 1]);
        parent->elements[pos - 1] = sibling->elements[sibling->elements.size() - 1];
        toUpdate->children.template emplace(toUpdate->children.begin(), sibling->children[sibling->children.size() - 1]);
        sibling->elements.pop_back();
        sibling->children.pop_back();
        toUpdate->children[0]->parent = toUpdate;
    } else {
        int pos = 0;
        for (int i = 0; i < parent->children.size(); i++) {
            if (parent->children[i] == toUpdate) {
                pos = i;
            }
        }
        toUpdate->elements.template emplace_back(parent->elements[pos]);
        parent->elements[pos] = sibling->elements[0];
        toUpdate->children.template emplace_back(sibling->children[0]);
        sibling->elements.erase(sibling->elements.begin());
        sibling->children.erase(sibling->children.begin());
        toUpdate->children[toUpdate->children.size() - 1]->parent = toUpdate;
    }
}

void BPlusTree::updateKeys(Node *toUpdate, const int key) {
    if (toUpdate == nullptr) {
        return;
    }
    if (toUpdate->contain(key)) {
        Element successor = getSuccessor(toUpdate, key);
        int pos = toUpdate->findPosition(key);
        toUpdate->elements[pos] = successor;
    }
    if (toUpdate->elements.size() < power - 1 && toUpdate != root) {
        Node* left = toUpdate->leftSibling;
        Node* right = toUpdate->rightSibling;
        if (left != nullptr && left->elements.size() > power - 1 && left->parent == toUpdate->parent) {
            borrowElementInternal(toUpdate, left);
        } else if (right != nullptr && right->elements.size() > power - 1 && right->parent == toUpdate->parent) {
            borrowElementInternal(toUpdate, right);
        } else {
            if (left != nullptr && left->parent == toUpdate->parent) {
                mergeWithParent(toUpdate, left);
            } else {
                mergeWithParent(toUpdate, right);
            }
        }
    }
    updateKeys(toUpdate->parent, key);
}

void BPlusTree::split(Node *toSplit) {
    Element midEl = toSplit->elements[power];
    Node* afterSplit = moveHalfNodeToNewOne(toSplit);
    if (toSplit == this->root) {
        this->root = new Node(false, {midEl}, {toSplit, afterSplit});
        toSplit->parent = root;
        afterSplit->parent = root;
    } else {
        Node* parent = toSplit->parent;
        afterSplit->parent = parent;
        int pos = 0;
        while (pos < parent->elements.size() && parent->elements[pos].key < midEl.key) {
            pos++;
        }
        auto it1 = parent->elements.begin() + pos;
        parent->elements.emplace(it1, midEl);
        auto it2 = parent->children.begin() + pos + 1;
        parent->children.emplace(it2, afterSplit);
        if (parent->elements.size() == 2 * power) {
            split(parent);
        }
    }
}

void BPlusTree::mergeLeaves(Node *left, Node *right) {
    Node* parent = right->parent;

    for (int i = 0; i < right->elements.size(); i++){
        left->elements.template emplace_back(right->elements[i]);
    }

    if (right->rightSibling != nullptr)
        right->rightSibling->leftSibling = left;
    left->rightSibling = right->rightSibling;

    int minRightKey = right->elements[0].key;
    int pos = parent->findPosition(minRightKey);

    parent->elements.erase(parent->elements.begin() + pos);
    parent->children.erase(parent->children.begin() + pos + 1);

    if (parent == root && parent->elements.size() == 0){
        root = left;
        left->parent = right->parent = nullptr;
    }
    delete right;
}

void BPlusTree::erase(Node *toDelete, int key) {
    toDelete->elements.erase(toDelete->elements.begin() + toDelete->findPosition(key));
    if (toDelete == root && root->elements.size() == 0) {
        root = nullptr;
        return;
    }
    if (toDelete->elements.size() >= power - 1) {
        updateKeys(toDelete->parent, key);
        return;
    }
    Node* left = toDelete->leftSibling;
    Node* right = toDelete->rightSibling;
    if (left != nullptr && left->elements.size() > power - 1 && left->parent == toDelete->parent) {
        auto it = toDelete->elements.begin();
        int indexLastElement = left->elements.size() - 1;
        int pos = left->parent->findPositionInChildrenByNode(left);
        toDelete->elements.template emplace(it, left->elements[indexLastElement]);
        left->parent->elements[pos] = toDelete->elements[0];
        left->elements.pop_back();
        updateKeys(toDelete->parent, key);
        return;
    }
    if (right != nullptr && right->elements.size() > power - 1 && right->parent == toDelete->parent) {
        int keyBorrowedElement = right->elements[0].key;
        toDelete->elements.template emplace_back(right->elements[0]);
        right->elements.erase(right->elements.begin());
        int pos = toDelete->parent->findPosition(keyBorrowedElement);
        toDelete->parent->elements[pos] = right->elements[0];
        updateKeys(toDelete->parent, key);
        return;
    }
    if (left != nullptr && left->parent == toDelete->parent){
        mergeLeaves(left, toDelete);
        updateKeys(left->parent, key);
    }
    if (right != nullptr && right->parent == toDelete->parent) {
        mergeLeaves(toDelete, right);
        updateKeys(toDelete->parent, key);
    }
}

void BPlusTree::mergeWithParent(Node *toUpdate, Node *sibling) {
    Node* parent = toUpdate->parent;
    if (sibling == toUpdate->leftSibling) {
        int pos = parent->findPositionInChildrenByNode(toUpdate);
        sibling->elements.template emplace_back(parent->elements[pos - 1]);
        for (int i = 0; i < toUpdate->elements.size(); i++) {
            sibling->elements.template emplace_back(toUpdate->elements[i]);
        }
        for (int i = 0; i < toUpdate->children.size(); i++) {
            sibling->children.template emplace_back(toUpdate->children[i]);
            toUpdate->children[i]->parent = sibling;
        }
        if (toUpdate->rightSibling != nullptr) {
            toUpdate->rightSibling->leftSibling = sibling;
        }
        sibling->rightSibling = toUpdate->rightSibling;
        parent->elements.erase(parent->elements.begin() + pos - 1);
        parent->children.erase(parent->children.begin() + pos);
    } else {
        int pos = parent->findPositionInChildrenByNode(sibling);
        toUpdate->elements.template emplace_back(parent->elements[pos - 1]);
        for (int i = 0; i < sibling->elements.size(); i++) {
            toUpdate->elements.template emplace_back(sibling->elements[i]);
        }
        for (int i = 0; i < sibling->children.size(); i++) {
            toUpdate->children.template emplace_back(sibling->children[i]);
            sibling->children[i]->parent = toUpdate;
        }
        if (sibling->rightSibling != nullptr) {
            sibling->rightSibling->leftSibling = toUpdate;
        }
        toUpdate->rightSibling = sibling->rightSibling;
        parent->elements.erase(parent->elements.begin() + pos - 1);
        parent->children.erase(parent->children.begin() + pos);
    }
    if (parent == root && parent->elements.size() == 0) {
        if (sibling == toUpdate->leftSibling) {
            root = sibling;
        } else {
            root = toUpdate;
        }
        sibling->parent = toUpdate->parent = nullptr;
        delete parent;
    }
}

BPlusTree::BPlusTree(const int &power) {
    this->power = power;
    root = nullptr;
}

BPlusTree::~BPlusTree() {
    root->free(root);
}

void BPlusTree::erase(int key) {
    Node* toDelete = findLeaf(root, key);
    if (toDelete == root && toDelete->elements.size() == 1) {
        root = nullptr;
        return;
    }
    erase(toDelete, key);
}

void BPlusTree::insert(const int &key, const string &data) {
    auto* element = new Element(key, data);
    if (root == nullptr) {
        std::vector<Element> vector = {*element};
        root = new Node(true, vector, {nullptr, nullptr});
        return;
    }
    Node* toInsert = findLeaf(root, key);
    int pos = 0;
    while (pos < toInsert->elements.size() && toInsert->elements[pos].key < key) {
        pos++;
    }
    auto it = toInsert->elements.begin() + pos;
    toInsert->elements.emplace(it, *element);
    toInsert->children.emplace_back(nullptr);
    if(toInsert->elements.size() == power * 2) {
        split(toInsert);
    }
}

void BPlusTree::print() {
    std::cout << "\nTree: \n";
    if (root != nullptr) {
        root->print(0);
    } else {
        std::cout << "Tree is empty\n";
    }
}

string BPlusTree::search(int key) {
    Node* toFind = findLeaf(root, key);
    int pos = 0;
    while (pos < toFind->elements.size() && toFind->elements[pos].key < key) {
        pos++;
    }
    return toFind->elements[pos].data;
}
