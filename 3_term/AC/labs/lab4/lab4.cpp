#include <iostream>

template<typename T>
class Node {
public:
    int key;
    T data;

    Node() = default;

    Node(int Key, T Data) {
        key = Key;
        data = Data;
    }
};

template<typename T>
class DataSet {
private:
    int capacity;

    void grow_capacity();

public:
    int size;
    Node<T>* elements;

    DataSet();

    void add_element(int key, T data);

    void print();

    void sort1();

    void sort2();

    void sort3();
};

template<typename T>
void DataSet<T>::grow_capacity() {
    if (capacity < 100) capacity *= 4;
    else capacity *= 2;

    Node<T>* tmp = elements;
    elements = new Node<T>[capacity];
    for (int i = 0; i < size; i++)
        elements[i] = tmp[i];
    delete tmp;
}

template<typename T>
DataSet<T>::DataSet() {
    size = 0;
    capacity = 1;
    elements = new Node<T>[capacity];
}

template<typename T>
void DataSet<T>::add_element(int key, T data) {
    if (size == capacity) grow_capacity();
    elements[size] = { key, data };
    size++;
}

template<typename T>
void DataSet<T>::print() {
    for (int i = 0; i < size; i++)
        std::cout << elements[i].data << '(' << elements[i].key << ')' << "  ";
    std::cout << std::endl;
}

template<typename T>
void DataSet<T>::sort1() {
    DataSet<T> subset0, subset1;
    for (int i = 0; i < size; i++) {
        if (elements[i].key == 0)
            subset0.add_element(0, elements[i].data);
        else
            subset1.add_element(1, elements[i].data);
    }

    for (int i = 0; i < subset0.size; i++) {
        elements[i] = subset0.elements[i];
    }

    for (int i = 0; i < subset1.size; i++) {
        elements[subset0.size + i] = subset1.elements[i];
    }
}

template<typename T>
void DataSet<T>::sort2() {
    int left = 0, right = size - 1;
    bool flag;
    while (left < right) {
        flag = false;
        if (elements[left].key == 0) {
            left++;
            flag = true;
        }
        if (elements[right].key == 1) {
            right--;
            flag = true;
        }
        if (flag) continue;
        Node<T> tmp = elements[right];
        elements[right] = elements[left];
        elements[left] = tmp;
    }
}

template<typename T>
void DataSet<T>::sort3() {
    bool flag;
    for (int i = 0; i < size; i++) {
        flag = true;
        for (int j = 0; j < size - 1; j++) {
            if (elements[j + 1].key < elements[j].key) {
                flag = false;
                Node<T> tmp = elements[j + 1];
                elements[j + 1] = elements[j];
                elements[j] = tmp;
            }
        }
        if (flag) break;
    }
}

int main() {
    return 0;
}