#include "SplayTree.h"

Node::Node() {
    value = 0;
    left = right = parent = nullptr;
}

Node::Node(int value) {
    this->value = value;
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
    cout << node->value << "\n";
    output(node->left, space);
}

SplayTree::SplayTree() {
    root = nullptr;
}

void SplayTree::splay(Node *toSplay, Node *rootSplay) {
    Node* parent = rootSplay->parent;
    while (toSplay->parent != parent){
        if (toSplay->parent->parent == nullptr) {
            if (toSplay == toSplay->parent->left) {
                zig(toSplay, true);
            } else {
                zig(toSplay, false);
            }
        } else {
            if (toSplay == toSplay->parent->left) {
                if (toSplay->parent == toSplay->parent->parent->left) {
                    zig_zig(toSplay, true);
                } else {
                    zig_zag(toSplay, false);
                }
            } else {
                if (toSplay->parent == toSplay->parent->parent->right) {
                    zig_zig(toSplay, false);
                } else {
                    zig_zag(toSplay, true);
                }
            }
        }
    }
    if (parent == nullptr) {
        root = toSplay;
    }
}

void SplayTree::zig(Node *toSplay, bool leftSide) {
    cout<< "zig " << leftSide << " " << toSplay->value << endl;
    Node* parent = toSplay->parent;
    if (leftSide) {
        parent->left = toSplay->right;
        if (toSplay->right != nullptr) {
            parent->left->parent = parent;
        }
        toSplay->right = parent;
    } else {
        parent->right = toSplay->left;
        if (toSplay->left != nullptr) {
            parent->right->parent = parent;
        }
        toSplay->left = parent;
    }
    toSplay->parent = parent->parent;
    if (toSplay->parent != nullptr) {
        if (parent == toSplay->parent->left) {
            toSplay->parent->left = toSplay;
        } else {
            toSplay->parent->right = toSplay;
        }
    }
    parent->parent = toSplay;
}
void SplayTree::zig_zig(Node *toSplay, bool leftSide) {
    cout<< "zig-zig " << leftSide << " " << toSplay->value << endl;
    Node* parent = toSplay->parent;
    Node* gran = parent->parent;
    if (leftSide) {
        gran->left = parent->right;
        if (parent->right != nullptr) {
            gran->left->parent = gran;
        }
        parent->left = toSplay->right;
        if (toSplay->right != nullptr) {
            parent->left->parent = parent;
        }
        parent->right = gran;
        toSplay->right = parent;
    } else {
        gran->right = parent->left;
        if(parent->left != nullptr) {
            gran->right->parent = gran;
        }
        parent->right = toSplay->left;
        if(toSplay->left != nullptr) {
            parent->right->parent = parent;
        }
        parent->left = gran;
        toSplay->left = parent;
    }
    toSplay->parent = gran->parent;
    if (gran->parent != nullptr) {
        if (gran == gran->parent->left) {
            gran->parent->left = toSplay;
        } else {
            gran->parent->right = toSplay;
        }
    }
    gran->parent = parent;
    parent->parent = toSplay;
}

void SplayTree::zig_zag(Node *toSplay, bool leftSide) {
    cout<< "zig-zag " << leftSide << " " << toSplay->value << endl;
    Node* parent = toSplay->parent;
    Node* grand = parent->parent;
    if (leftSide) {
        parent->right = toSplay->left;
        if (toSplay->left != nullptr) {
            parent->right->parent = parent;
        }
        grand->left = toSplay->right;
        if (toSplay->right != nullptr) {
            grand->left->parent = parent;
        }
        toSplay->left = parent;
        toSplay->right = grand;
        parent->parent = toSplay;
    } else {
        parent->left = toSplay->right;
        if (toSplay->right != nullptr) {
            parent->left->parent = parent;
        }
        grand->right = toSplay->left;
        if (toSplay->left != nullptr) {
            grand->right->parent = parent;
        }
        toSplay->right = parent;
        toSplay->left = grand;
        parent->parent = toSplay;
    }
    toSplay->parent = grand->parent;
    if (grand->parent != nullptr) {
        if (grand == grand->parent->left) {
            grand->parent->left = toSplay;
        } else {
            grand->parent->right = toSplay;
        }
    }
    grand->parent = toSplay;
}

void SplayTree::insert(int &t) {
    if (root == nullptr) {
        root = new Node(t);
        return;
    } else {
        split(t);
    }
}

void SplayTree::erase(int &t) {
    Node* toDelete = get(root, t);
    std::cout << toDelete->value << std::endl;
    splay(toDelete, root);
    merge(root->left, root->right);
    if (root != nullptr) {
        root->parent = nullptr;
    }
}

void SplayTree::output() const {
    cout << "\nTree:\n";
    root->output(root, 0);
}

void SplayTree::split(const int &t) {
    Node* successor = nullptr;
    Node* temp = root;
    while (temp != nullptr) {
        if (temp->value == t) {
            successor = temp;
            break;
        }
        if (temp->value > t) {
            successor = temp;
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    if (successor == nullptr) {
        successor = root;
        while (successor->right != nullptr) {
            successor = successor->right;
        }
    }
    splay(successor, root);
    Node* toInsert = new Node(t);
    if (successor->value >= toInsert->value) {
        toInsert->left = successor->left;
        if (toInsert->left != nullptr) {
            toInsert->left->parent = toInsert;
        }
        successor->left = nullptr;
        toInsert->right = successor;
    } else {
        toInsert->left = successor;
    }
    successor->parent = toInsert;
    root = toInsert;
}

void SplayTree::merge(Node *rootLeft, Node *rootRight) {
    if (rootLeft == nullptr && rootRight == nullptr){
        root = nullptr;
        return;
    }
    if (rootLeft == nullptr){
        root = rootRight;
        return;
    }
    if (rootRight == nullptr){
        root = rootLeft;
        return;
    }
    Node* maxLeft = rootLeft->right;
    if (maxLeft == nullptr) {
        rootLeft->right = rootRight;
        rootRight->parent = rootLeft;
        this->root = rootLeft;
        return;
    }
    while (maxLeft->right != nullptr) {
        maxLeft = maxLeft->right;
    }
    splay(maxLeft, rootLeft);
    maxLeft->right = rootRight;
    rootRight->parent = maxLeft;
    this->root = maxLeft;
}

Node* SplayTree::get(Node *node, const int &t) {
    if (node == nullptr) {
        return nullptr;
    }
    if (t == node->value) {
        return node;
    }
    if (t < node->value) {
        return get(node->left, t);
    } else {
        return get(node->right, t);
    }
}
