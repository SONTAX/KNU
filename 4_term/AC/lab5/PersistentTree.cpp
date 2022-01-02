#include "PersistentTree.h"

Node::Node(int key) {
    key = key;
    _color = RED;
    left = right = parent = nullptr;
}

Node::Node(Node* node, Node* _parent) {
    parent = _parent;
    left = node->left;
    right= node->right;
    key = node->key;
    _color = node->_color;
    if (node->left != nullptr) {
        node->left->parent = this;
    }
    if (node->right != nullptr) {
        node->right->parent = this;
    }
    if (_parent != nullptr) {
        if (_parent->right == node) {
            _parent->right = this;
        } else {
            _parent->left = this;
        }
    }
}

void Node::output(Node* node, int space) const {
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
    output(node->left, space);
}

void PersistentTree::clearMemory(Node* node) {
    if (node != nullptr){
        if (node->right != nullptr) {
            clearMemory(node->right);
        }
        if (node->left != nullptr) {
            clearMemory(node->left);
        }
        node = nullptr;
    }
}

void PersistentTree::fixInsertion(Node* node) {
    if (node == root) {
        root->_color = BLACK;
        return;
    }
    while (node->parent != nullptr && node->parent->_color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle;
            if (node->parent->parent->right == nullptr) {
                uncle = nullptr;
            } else {
                uncle = new Node(node->parent->parent->right, node->parent->parent);
            }
            if (uncle != nullptr && uncle->_color == RED) {
                node->parent->_color = BLACK;
                uncle->_color = BLACK;
                node->parent->parent->_color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->_color = BLACK;
                node->parent->parent->_color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            Node* uncle;
            if (node->parent->parent->left == nullptr) {
                uncle = nullptr;
            } else {
                uncle = new Node(node->parent->parent->left, node->parent->parent);
            }
            if (uncle != nullptr && uncle->_color == RED) {
                node->parent->_color = BLACK;
                uncle->_color = BLACK;
                node->parent->parent->_color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
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

void PersistentTree::fixErasing(Node* node) {
    while (node != root && node->_color == BLACK) {
        Node* parent = node->parent;
        if (parent->left == node) {
            Node* brother = new Node(parent->right, parent);
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;
                leftRotate(parent);
                brother = new Node(parent->right, parent);
            }
            if ((brother->left == nullptr || brother->left->_color == BLACK) &&
                (brother->right == nullptr || brother->right->_color == BLACK)) {
                brother->_color = RED;
                node = node->parent;
            } else {
                if (brother->right == nullptr || brother->right->_color == BLACK) {
                    brother->_color = RED;
                    Node* brotherLeft = new Node(brother->left, brother);
                    brotherLeft->_color = BLACK;
                    rightRotate(brother);
                    brother = new Node(parent->right, parent);
                }
                brother->_color = parent->_color;
                parent->_color = BLACK;
                if (brother->right) {
                    Node* brotherRight = new Node(brother->right, brother);
                    brotherRight->_color = BLACK;
                }
                leftRotate(parent);
                node = root;
            }
        } else {
            Node* brother = new Node(parent->left, parent);
            if (brother->_color == RED) {
                brother->_color = BLACK;
                parent->_color = RED;
                rightRotate(parent);
                brother = new Node(parent->left, parent);
            }
            if ((brother->left == nullptr || brother->left->_color == BLACK) &&
                (brother->right == nullptr || brother->right->_color == BLACK)) {
                brother->_color = RED;
                node = node->parent;
            } else {
                if (brother->left == nullptr || brother->left->_color == BLACK) {
                    brother->_color = RED;
                    Node* brotherRight = new Node(brother->right, brother);
                    brotherRight->_color = BLACK;
                    leftRotate(brother);
                    brother = new Node(parent->left, parent);
                }
                brother->_color = parent->_color;
                parent->_color = BLACK;
                if (brother->left) {
                    Node* brotherLeft = new Node(brother->left, brother);
                    brotherLeft->_color = BLACK;
                }
                rightRotate(parent);
                node = root;
            }
        }
    }
    node->_color = BLACK;
}

void PersistentTree::leftRotate(Node* node) {
    Node* rightSon = new Node(node->right, node);
    node->right = rightSon->left;
    if (rightSon->left != nullptr) {
        rightSon->left->parent = node;
    }
    rightSon->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightSon;
    } else if (node == node->parent->left) {
        node->parent->left = rightSon;
    } else {
        node->parent->right = rightSon;
    }
    rightSon->left = node;
    node->parent = rightSon;
}

void PersistentTree::rightRotate(Node *node) {
    Node* leftSon = new Node(node->left, node);
    node->left = leftSon->right;
    if (leftSon->right != nullptr) {
        leftSon->right->parent = node;
    }
    leftSon->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftSon;
    } else if (node == node->parent->left) {
        node->parent->left = leftSon;
    } else {
        node->parent->right = leftSon;
    }
    leftSon->right = node;
    node->parent = leftSon;
}

void PersistentTree::backUpPreviousRoot(Node* newRoot) {
    root = newRoot;
    backUpTree(root);
}

void PersistentTree::backUpTree(Node *node) {
    if (node != nullptr) {
        if (node->left != nullptr) {
            node->left->parent = node;
            backUpTree(node->left);
        }
        if (node->right != nullptr) {
            node->right->parent = node;
            backUpTree(node->right);
        }
    }
}

void PersistentTree::erase(Node *node) {
    if (node == root && node->left == nullptr && node->right == nullptr) {
        delete root;
        root = nullptr;
        previousRoots.push_back(nullptr);
        return;
    }
    Node* tempNode;
    Node* parent = node->parent;
    if (node->_color == RED) {
        if (node->right == nullptr && node->left == nullptr) {
            if (parent->right == node) {
                parent->right = nullptr;
            }
            else {
                parent->left = nullptr;
            }
            delete node;
            previousRoots.push_back(root);
            return;
        } else {
            tempNode = getSuccessor(node);
            node->key = tempNode->key;
            erase(tempNode);
            return;
        }
    } else {
        if (node->right == nullptr && node->left == nullptr) {
            fixErasing(node);
            if (parent->left == node) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            delete node;
            previousRoots.push_back(root);
            return;
        }
        if (node->right == nullptr || node->left == nullptr) {
            if (node->right != nullptr) {
                node->key = node->right->key;
                node->right = nullptr;
            } else {
                node->key = node->left->key;
                node->left = nullptr;
            }
            previousRoots.push_back(root);
            return;
        }
        if (node->right != nullptr && node->left != nullptr) {
            tempNode = getSuccessor(node);
            node->key = tempNode->key;
            erase(tempNode);
            return;
        }
    }
}

PersistentTree::PersistentTree() {
    root = nullptr;
    previousRoots.clear();
}

PersistentTree::~PersistentTree() {
    for (auto i : previousRoots) {
        clearMemory(i);
    }
}

Node* PersistentTree::getSuccessor(Node* node) {
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

Node* PersistentTree::getMinNode(Node *node) const {
    while (node && node->left) {
        node = new Node(node->left, node);
    }
    return node;
}

Node* PersistentTree::search(int data) {
    Node* temp = new Node(root, nullptr);
    root = temp;
    while (temp != nullptr && temp->key != data){
        if (temp->key < data) {
            if (temp->right == nullptr) {
                temp = nullptr;
            } else {
                temp = new Node(temp->right, temp);
            }
        } else {
            if (temp->left == nullptr) {
                temp = nullptr;
            } else {
                temp = new Node(temp->left, temp);
            }
        }
    }
    return temp;
}

void PersistentTree::insert(int data) {
    Node *node = new Node(data);
    if (root == nullptr) {
        root = node;
        root->parent = nullptr;
        previousRoots.push_back(root);
        fixInsertion(root);
    }
    Node* temp = new Node(root, nullptr);
    root = temp;
    Node* parent;
    while (temp != nullptr) {
        parent = temp;
        if (temp->key < node->key) {
            if (temp->right == nullptr) {
                temp = nullptr;
            } else {
                temp = new Node(temp->right, temp);
            }
        } else {
            if (temp->left == nullptr) {
                temp = nullptr;
            } else {
                temp = new Node(temp->left, temp);
            }
        }
    }
    node->parent = parent;
    if (parent->key > node->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    fixInsertion(node);
    previousRoots.push_back(root);
}

void PersistentTree::erase(int data) {
    Node* node = search(data);
    if (node == nullptr){
        cout << "There isn't vertex with given data\n";
        return;
    }
    erase(node);
}

void PersistentTree::output() const {
    cout << "\nTree:\n";
    if (root == nullptr) {
        cout << "Tree is empty\n";
        return;
    }
    root->output(root, 0);
}

void PersistentTree::DumpAllRoots() {
    for (int i = 0; i < previousRoots.size(); i++) {
        cout << "---------------------------------" << i << "--------------------------\n";
        backUpPreviousRoot(previousRoots[i]);
        Dump();
    }
}


