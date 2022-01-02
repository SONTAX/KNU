#include "FibonacciHeap.h"

int main() {
    FibonacciHeap heap;
    Node* temp;
    Node* node1;
    Node* node2;
    Node* node3;
    Node* node4;
    cout << "INSERT 15 NODES\n\n";
    for (int i = 0; i < 15; i++) {
        temp = heap.insert(i + 1);
        if (i == 8)
            node1 = temp;
        if (i == 7)
            node3 = temp;
        if (i == 6)
            node2 = temp;
        if (i == 11)
            node4 = temp;
    }
    heap.print();
    std::cout << "\n\nEXTRACT MIN\n\n";
    heap.extractMin();
    heap.print();
    return 0;
}