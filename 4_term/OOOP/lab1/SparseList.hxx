#ifndef SPARSELIST_HXX_
#define SPARSELIST_HXX_

#include "SparseList.h"

template<typename T>
void SparseList<T>::Add(T val) {
	if (val) {
		Node<T>* new_node = new Node<T>;
		new_node->value = val;
		new_node->index = list_size;
		if (pbeg == nullptr) {
			pbeg = new_node;
			pend = new_node;
		}
		else {
			new_node->prev = pend;
			pend->next = new_node;
			pend = new_node;
		}
	}
	if (!was_zero) {
		if (val == 0) {
			was_zero = true;
			zero_index = list_size;
		}
	}
	list_size++;
}

template<typename T>
string SparseList<T>::PrintAll() {
	string output;
	Node<T>* current = pbeg;
	for (size_t i = 0; i < list_size; i++) {
		if (current) {
			if (i == current->index) {
				output += to_string(current->value) + " ";
				current = current->next;
			}
			else {
				output += "0 ";
			}
		}
		else {
			output += "0 ";
		}
	}
	return output;
}

template<typename T>
void SparseList<T>::GetList(size_t lenth) {
	DeleteList();
	int input;
	for (size_t i = 0; i < lenth; i++) {
		cin >> input;
		Add(input);
	}
}

template<typename T>
int SparseList<T>::GetIndex(T val) {
	if (val != 0) {
		Node<T>* current = pbeg;
		while (current) {
			if (current->value == val) {
				return current->index;
			}
			current = current->next;
		}
		return -1;
	}
	else {
		return zero_index;
	}
}

template<typename T>
T SparseList<T>::GetValue(size_t ind) {
	if (ind < list_size) {
		Node<T>* current = pbeg;
		while (current) {
			if (current->index == ind) {
				return current->value;
			}
			current = current->next;
		}
		return 0;
	}
	else {
		return -1;
	}
}

template<typename T>
void SparseList<T>::GetRandomList(size_t lenth) {
	DeleteList();
	T val;
	for (size_t i = 0; i < lenth; i++) {
		val = (rand() % 16) / 3;
		Add(val);
	}
}

template<typename T>
void SparseList<T>::DeleteList() {
	Node<T>* current = pbeg;
	while (current) {
		Node<T>* del = current;
		current = current->next;
		delete del;
	}
	pbeg = nullptr;
	pend = nullptr;
	list_size = 0;
}

#endif