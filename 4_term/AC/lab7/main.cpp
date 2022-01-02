#include "BinomialHeap.h"

int main() {
    BinomialHeap heap;
    for (int i = 0; i < 10; i++)
        heap.insert(i);
    std::cout << "NEW TREE\n";
    heap.print();

    std::cout << "EXTRACT MIN\n";
    heap.extractMin();
    heap.print();
    return 0;
}