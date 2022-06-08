#include <iostream>

struct Bolt {
    int val;
};

struct Nut {
    int val;
};

//функція для ініціалізації масивів болтів та гайок
void input(Bolt* A, Nut* B, int size) {
    std::cout << "Input bolts array: ";
    for (int i = 0; i < size; i++) {
        std::cin >> A[i].val;
    }
    std::cout << "Input nuts array: ";
    for (int i = 0; i < size; i++) {
        std::cin >> B[i].val;
    }
}

//функція, що виводить масив
template<typename T>
void arr_print(T* A, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << A[i].val << ' ';
    }
    std::cout << std::endl;
}

//функція, що виконує перерозподіл елементів у масивах болтів та гайок
int partition(Bolt* B, Nut* N, int left, int right) {
    int i_pivot = (left + right) / 2;
    Bolt pivot_1 = B[i_pivot];
    int i = left - 1;
    int i_tmp = 0;

    for (int j = left; j <= right; j++) {
        if (N[j].val == pivot_1.val) {
            i_tmp = j;
        }
        else {
            if (N[j].val < pivot_1.val) {
                i++;
                if (N[i].val == pivot_1.val) {
                    i_tmp = j;
                }
                std::swap(N[i], N[j]);
            }
        }
    }
    std::swap(N[i + 1], N[i_tmp]);
    std::swap(B[i + 1], B[i_pivot]);

    Nut pivot_2 = N[i + 1];
    i = left - 1;
    for (int j = left; j <= right; j++) {
        if (B[j].val < pivot_2.val) {
            i++;
            std::swap(B[i], B[j]);
        }
    }
    return (i + 1);
}

//рекурсивна функція швидкого сортування
void quickSort(Bolt* B, Nut* N, int left, int right) {
    if (left < right) {
        int p = partition(B, N, left, right);
        quickSort(B, N, left, p - 1);
        quickSort(B, N, p + 1, right);
    }
}

int main() {
    Bolt bolts[5];
    Nut nuts[5];
    input(bolts, nuts, 5);
    std::cout << std::endl;
    quickSort(bolts, nuts, 0, 4);
    std::cout << "Sorted bolts array: ";
    arr_print(bolts, 5);
    std::cout << "Sorted nuts array: ";
    arr_print(nuts, 5);
    return 0;
}