#include <iostream>
#include "RBTree.h"

int main() {
    RBTree tree;
    for (int i = 0; i < 5; i++) {
        tree.insert(i);
    }
    tree.Dump();
    return 0;
}
