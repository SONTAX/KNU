#include "RBTree.h"

Node::Node(int key) {
    key = key;
    _color = RED;
    size = 1;
    left = right = parent = nullptr;
}

void Node::output(Node *node, int space) const {
    if (node == nullptr) {
        return;
    }
    space += 10;
    output(node->right, space);
    cout << std::endl;
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    cout << node->key << ":";
    if(node->_color == BLACK) {
        cout << "B";
    }
    else if(node->_color == RED) {
        cout << "R";
    }
    cout << ": s = " << node->size << '\n';
    output(node->left, space);
}

void RBTree::clearMemory(Node* node) {
    if (node != nullptr) {
        if (node->right) {
            clearMemory(node->left);
        }
        if (node->left) {
            clearMemory(node->left);
        }
        delete node;
    }
}

RBTree::RBTree() {
    root = nullptr;
}
RBTree::~RBTree() {
    clearMemory(root);
}

Node* RBTree::search(int data) {
    Node* temp = root;
    while (temp != nullptr && temp->key != data) {
        if (temp->key > data) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    return temp;
}

Node* RBTree::getSuccessor(Node *node) {
    if (node->right) {
        return getMinNode(node->right);
    }
    Node* successor = node->parent;
    while (successor && successor->right == node) {
        node = successor;
        successor = successor->parent;
    }
    return successor;
}

Node* RBTree::getMinNode(Node *node) const{
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

Node* RBTree::getStat(Node* node, int index){
    int curPos = 1;
    if (node->left != nullptr) {
        curPos += node->left->size;
    }
    if(curPos == index) {
        return node;
    }
    if(curPos > index) {
        return getStat(node->left, index);
    }
    else {
        return getStat(node->right, index - curPos);
    }
}

int RBTree::getStat(int index){
    Node* res = getStat(root, index);
    return res->key;
}

void RBTree::insert(int data) {
    Node *node = new Node(data);
    if (root == nullptr){
        root = node;
        root->parent = nullptr;
        fixInsertion(root);
        return;
    }
    Node* x = root;
    Node* parent = nullptr;
    while (x != nullptr){
        parent = x;
        if (x->key < node->key) {
            x = x->right;
        }
        else {
            x = x->left;
        }
    }
    node->parent = parent;
    if (parent == nullptr) {
        root = node;
    }
    else{
        if (parent->key > node->key) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }
    }
    while (parent != nullptr){
        parent->size++;
        parent = parent->parent;
    }
    fixInsertion(node);
}

void RBTree::erase(int data){
    Node* node = search(data);
    if (node == nullptr){
        cout << "There isn't vertex with given data\n";
        return;
    }
    erase(node);
}

void RBTree::erase(Node *node) {
    if (node == root && node->size == 1){
        clearMemory(root);
        root = nullptr;
        return;
    }
    Node* tempNode;
    Node* parent = node->parent;
    if (node->_color == RED){
        if (node->right == nullptr && node->left == nullptr){
            if (parent->right == node) {
                parent->right = nullptr;
            }
            else {
                parent->left = nullptr;
            }
            clearMemory(node);
            while (parent != nullptr){
                parent->size--;
                parent = parent->parent;
            }
            return;
        } else {
            tempNode = getSuccessor(node);
            node->key = tempNode->key;
            erase(tempNode);
            return;
        }
    } else {
        if (node->right == nullptr && node->left == nullptr){
            fixErasing(node);
            if (parent->left == node) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            clearMemory(node);
            while (parent != nullptr){
                parent->size--;
                parent = parent->parent;
            }
            return;
        }
        if (node->right == nullptr || node->left == nullptr){
            parent = node;
            if (node->right != nullptr) {
                node->key = node->right->key;
                clearMemory(node->right);
                node->right = nullptr;
            } else {
                node->key = node->left->key;
                clearMemory(node->left);
                node->left = nullptr;
            }
            while (parent != nullptr){
                parent->size--;
                parent = parent->parent;
            }
            return;
        }
        if (node->right != nullptr && node->left != nullptr){
            tempNode = getSuccessor(node);
            node->key = tempNode->key;
            erase(tempNode);
            return;
        }
    }
}

void RBTree::fixInsertion(Node *node) {
    if (node == root) {
        root->_color = BLACK;
        return;
    }
    while(node->parent != nullptr && node->parent->_color == RED){
        if (node->parent == node->parent->parent->left){
            Node* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->_color == RED){
                node->parent->_color = BLACK;
                uncle->_color = BLACK;
                node->parent->parent->_color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right){
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->_color = BLACK;
                node->parent->parent->_color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->_color == RED){
                node->parent->_color = BLACK;
                uncle->_color = BLACK;
                node->parent->parent->_color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left){
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->_color = BLACK;
                node->parent->parent->_color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->_color = BLACK;
}
void RBTree::fixErasing(Node *node) {
    while (node != root && node->_color == BLACK) {
        Node* parent = node->parent;
        if (parent->left == node) {
            Node* brother = parent->right;
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;
                leftRotate(parent);
                brother = parent->right;
            }
            if ((brother->left == nullptr || brother->left->_color == BLACK) &&
                (brother->right == nullptr || brother->right->_color == BLACK)) {
                brother->_color = RED;
                node = node->parent;
            } else {
                if (brother->right == nullptr || brother->right->_color == BLACK) {
                    brother->_color = RED;
                    brother->left->_color = BLACK;
                    rightRotate(brother);
                    brother = parent->right;
                }
                brother->_color = parent->_color;
                parent->_color = BLACK;
                if (brother->right) {
                    brother->right->_color = BLACK;
                }
                leftRotate(parent);
                node = root;
            }
        } else {
            Node* brother = parent->left;
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;
                rightRotate(parent);
                brother = parent->left;
            }
            if ((brother->left == nullptr || brother->left->_color == BLACK) &&
                (brother->right == nullptr || brother->right->_color == BLACK)) {
                brother->_color = RED;
                node = node->parent;
            } else {
                if (brother->left == nullptr || brother->left->_color == BLACK) {
                    brother->_color = RED;
                    brother->right->_color = BLACK;
                    leftRotate(brother);
                    brother = parent->left;
                }
                brother->_color = parent->_color;
                parent->_color = BLACK;
                if (brother->left)
                    brother->left->_color = BLACK;
                rightRotate(parent);
                node = root;
            }
        }
    }
    node->_color = BLACK;
}

void RBTree::leftRotate(Node *node) {
    Node *rightSon = node->right;
    node->right = rightSon->left;
    if (rightSon->left != nullptr) {
        rightSon->left->parent = node;
    }
    rightSon->parent = node->parent;
    if (node->parent == nullptr){
        root = rightSon;
    } else if (node == node->parent->left) {
        node->parent->left = rightSon;
    }
    else {
        node->parent->right = rightSon;
    }
    rightSon->left = node;
    node->parent = rightSon;
    rightSon->size = node->size;
    node->size = 1;
    if (node->left != nullptr) {
        node->size += node->left->size;
    }
    if (node->right != nullptr) {
        node->size += node->right->size;
    }
}
void RBTree::rightRotate(Node *node) {
    Node *leftSon = node->left;
    node->left = leftSon->right;
    if (leftSon->right != nullptr) {
        leftSon->right->parent = node;
    }
    leftSon->parent = node->parent;
    if (node->parent == nullptr){
        root = leftSon;
    } else if (node == node->parent->left) {
        node->parent->left = leftSon;
    }
    else {
        node->parent->right = leftSon;
    }
    leftSon->right = node;
    node->parent = leftSon;
    leftSon->size = node->size;
    node->size = 1;
    if (node->left != nullptr) {
        node->size += node->left->size;
    }
    if (node->right != nullptr) {
        node->size += node->right->size;
    }
}

void RBTree::output() const {
    cout << "\nTree:\n";
    if (root == nullptr){
        cout << "Tree is empty\n";
        return;
    }
    root->output(root, 0);
}