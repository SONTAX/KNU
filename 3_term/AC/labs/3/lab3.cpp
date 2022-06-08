#include <iostream> 

using namespace std;

//функція, яка будує або відновлює незростаючу властивість d-арної піраміди
void restoreDown(int arr[], int len, int index, int d) {
	int* child = new int[d + 1];
	while (1) {
		for (int i = 1; i <= d; i++) {
			if ((d * index + i) < len) {
				child[i] = d * index + i;
			}
			else {
				child[i] = -1;
			}
		}
		int max_child = -1, max_child_index; 
		for (int i = 1; i <= d; i++) {
			if ((child[i] != -1) && (arr[child[i]] > max_child)) {
				max_child_index = child[i];
				max_child = arr[child[i]];
			}
		}
		if (max_child == -1) {
			break;
		}
		if (arr[index] < arr[max_child_index]) {
			swap(arr[index], arr[max_child_index]);
		}
		index = max_child_index;
	}
}

//функція, яка відновлює даний вузол в купі
void restoreUp(int arr[], int index, int d) {
	int parent = (index - 1) / d;
	while (parent >= 0) {
		if (arr[index] > arr[parent]) {
			swap(arr[index], arr[parent]);
			index = parent;
			parent = (index - 1) / d;
		}
		else {
			break;
		}
	}
}

//функція, яка збільшує значення key на plus
void increaseKey(int arr[], int key, int d, int plus) {
	int index = 0;
	int i = 0;
	while (true) {
		if (arr[i] == key) {
			index = i;
			break;
		}
		i++;
	}
	arr[index] += plus;
	restoreUp(arr, index, d);
}

//функція, яка будує d-арну піраміду
void buildHeap(int arr[], int n, int d) {
	for (int i = (n - 1) / d; i >= 0; i--)
		restoreDown(arr, n, i, d);
}

//функція, яка додає задане значення у d-арну піраміду
void insert(int arr[], int* n, int d, int elem) {
	arr[*n] = elem;
	*n = *n + 1;
	restoreUp(arr, *n - 1, d);
}

//функція, яка вилучає найбільше значення d-арної піраміди
int extractMax(int arr[], int* n, int d) {
	int max = arr[0];
	arr[0] = arr[*n - 1];
	*n = *n - 1;
	restoreDown(arr, *n, 0, d);
	return max;
}

int main() {
	return 0;
}
