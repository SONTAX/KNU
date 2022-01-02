#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

struct Graph
{
    int ver_1;
    int ver_2;
    Graph* prev;
    Graph* next;
};

void PrintMatr(int** mas, int m)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            cout << mas[i][j] << " ";
        cout << endl;
    }
    system("pause");
}

int Menu()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 5) % 5;
        if (key == 0) cout << "-> Увести граф з клавіатури та зберегти у файл" << endl;
        else  cout << "   Увести граф з клавіатури та зберегти у файл" << endl;
        if (key == 1) cout << "-> Вивести матрицю суміжності" << endl;
        else  cout << "   Вивести матрицю суміжності" << endl;
        if (key == 2) cout << "-> Сортувати вершини за кількістю вихідних ребер" << endl;
        else  cout << "   Сортувати вершини за кількістю вихідних ребер" << endl;
        if (key == 3) cout << "-> Увести граф з файлу" << endl;
        else  cout << "   Увести граф з файлу" << endl;
        if (key == 4) cout << "-> Завершити роботу" << endl;
        else  cout << "   Завершити роботу" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

Graph* first(int a, int b)
{
    Graph* pv = new Graph;
    pv->ver_1 = a;
    pv->ver_2 = b;
    pv->next = 0;
    pv->prev = 0;
    return pv;
}

void add(Graph** pend, int a, int b)
{
    Graph* pv = new Graph;
    pv->ver_1 = a;
    pv->ver_2 = b;
    pv->next = 0;
    pv->prev = *pend;
    (*pend)->next = pv;
    *pend = pv;
}

int increment(int inc[], int size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do
    {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else
        {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

int Find(int a[], int pos, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] == pos)
        {
            pos = i + 1;
            i = size;
        }
    }
    return pos;
}

void Swap(int* a, int i)
{
    int temp;
    temp = a[i];
    a[i] = a[i - 1];
    a[i - 1] = temp;
}

void Merge(int* A, int first, int last)
{
    int middle, start, final, j;
    int* arr = new int[100];
    middle = (first + last) / 2;
    start = first;
    final = middle + 1;
    for (j = first; j <= last; j++)
        if ((start <= middle) && ((final > last) || (A[start] < A[final])))
        {
            arr[j] = A[start];
            start++;
        }
        else
        {
            arr[j] = A[final];
            final++;
        }
    for (j = first; j <= last; j++) A[j] = arr[j];
    delete[]arr;
}

int SortMenu()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 7) % 7;
        cout << "Оберіть метод сортування" << endl << endl;
        if (key == 0) cout << "-> Вставками" << endl;
        else  cout << "   Вставками" << endl;
        if (key == 1) cout << "-> Бульбашкою" << endl;
        else  cout << "   Бульбашкою" << endl;
        if (key == 2) cout << "-> Перемішуванням" << endl;
        else  cout << "   Перемішуванням" << endl;
        if (key == 3) cout << "-> Швидке" << endl;
        else  cout << "   Швидке" << endl;
        if (key == 4) cout << "-> Злиттям" << endl;
        else  cout << "   Злиттям" << endl;
        if (key == 5) cout << "-> Шелла" << endl;
        else  cout << "   Шелла" << endl;
        if (key == 6) cout << "-> Назад" << endl;
        else  cout << "   Назад" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

void InsertSort(int* a, int size)
{
    int tmp;
    for (int i = 1, j; i < size; ++i)
    {
        tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; --j)
            a[j + 1] = a[j];
        a[j + 1] = tmp;  
    }
}

void BubbleSort(int* a, int size)
{
    int tmp;

    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if (a[j + 1] < a[j])
            {
                tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void ShellSort(int* a, int size)
{
    int inc, i, j, seq[40];
    int s;

    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];
        for (i = inc; i < size; ++i)
        {
            int temp = a[i];
            for (j = i; (j >= inc) && (temp < a[j - inc]); j -= inc) {
                a[j] = a[j - inc];
            }
            a[j] = temp;
        }
    }
}

void QuickSort(int* a, int N)
{
    long i = 0, j = N;
    int temp, p;
    p = a[N >> 1];
    do {
        while (a[i] < p) i++;
        while (a[j] > p) j--;

        if (i <= j) {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++; j--;
        }
    } while (i <= j);
    if (j > 0) QuickSort(a, j);
    if (N > i) QuickSort(a + i, N - i);
}

void ShakerSort(int* a, int size)
{
    int Left, Right, i;
    Left = 1;
    Right = size - 1;
    while (Left <= Right)
    {
        for (i = Right; i >= Left; i--)
            if (a[i - 1] > a[i]) Swap(a, i);
        Left++;
        for (i = Left; i <= Right; i++)
            if (a[i - 1] > a[i]) Swap(a, i);
        Right--;
    }
}

void MergeSort(int* a, int first, int last)
{
    {
        if (first < last)
        {
            MergeSort(a, first, (first + last) / 2);
            MergeSort(a, (first + last) / 2 + 1, last);
            Merge(a, first, last);
        }
    }
}

int main()
{
    SetConsoleOutputCP(1251);
    int m = 0;
    int** mas;
    int* sorted;
    int* to_sort;
    mas = new int* [1];
    int answer;
    int ans;
    bool need;

    do
    {
        system("cls");
        answer = Menu();
        switch (answer)
        {
        case 0:
        {
            m = 0;
            while (m <= 0 || m > 10)
            {
                cout << "Введіть кількість вершин графа (до 10): ";
                while (!(cin >> m) || (cin.peek() != '\n'))
                {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Некорекиний ввід даних! Спробуйте знову: ";
                }
                cin.clear();
                if (m <= 0 || m > 10) cout << "Кількість вершин графа не може бути менше 1, або більше 10!" << endl;
            }
            mas = new int* [m];
            for (int i = 0; i < m; i++)
            {
                mas[i] = new int[m];
                for (int j = 0; j < m; j++)
                {
                    if (i == j)
                    {
                        system("cls");
                        cout << "Чи існує петля у вершині " << j + 1 << "?" << endl << "Введіть [0], якщо ні, або [1], якщо так: ";
                        while (!(cin >> need) || (cin.peek() != '\n'))
                        {
                            cin.clear();
                            while (cin.get() != '\n');
                            cout << "Некорекиний ввід даних! Спробуйте знову: ";
                        }
                        if (need) mas[i][j] = 1;
                        else mas[i][j] = 0;
                    }
                    else
                    {
                        system("cls");
                        cout << "Чи існує ребро з вершини " << i + 1 << " у вершину " << j + 1 << "?" << endl << "Введіть [0], якщо ні, або [1], якщо так: ";
                        while (!(cin >> need) || (cin.peek() != '\n'))
                        {
                            cin.clear();
                            while (cin.get() != '\n');
                            cout << "Некорекиний ввід даних! Спробуйте знову: ";
                        }
                        if (need) mas[i][j] = 1;
                        else mas[i][j] = 0;
                    }
                }
            }
            Graph* pbeg = new Graph;
            Graph* pend = pbeg;
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (mas[i][j] == 1)
                    {
                        add(&pend, i + 1, j + 1);
                    }
                }
            }
            pbeg = pbeg->next;
            pbeg->prev = nullptr;
            FILE* fp = fopen("Graph.dat", "wb");
            fwrite(&m, sizeof(int), 1, fp);
            Graph* p = pbeg;
            while (p)
            {
                fwrite(p, sizeof(Graph), 1, fp);
                p = p->next;
            }
            fclose(fp);
            break;
        }
        case 1:
        {
            if (m > 0) PrintMatr(mas, m);
            else
            {
                cout << "Некоректний ввід графу" << endl;
                system("pause");
            }
            break;
        }
        case 2:
        {
            if (m > 0)
            {
                to_sort = new int [m];
                sorted = new int [m];
                for (int i = 0; i < m; i++)
                {
                    to_sort[i] = 0;
                    sorted[i] = 0;
                }
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        to_sort[i] += mas[j][i];
                        sorted[i] += mas[j][i];
                    }
                }
                do
                {
                    ans = SortMenu();
                    switch (ans)
                    {
                    case 0:
                    {
                        InsertSort(sorted, m);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    case 1:
                    {
                        BubbleSort(sorted, m);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    case 2:
                    {
                        ShakerSort(sorted, m);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    case 3:
                    {
                        int n = m - 1;
                        QuickSort(sorted, n);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    case 4:
                    {
                        MergeSort(sorted, 0, m-1);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    case 5:
                    {
                        ShellSort(sorted, m);
                        for (int i = 0; i < m; i++)
                        {
                            cout << sorted[i] << "   ---   кількість вихідних ребер у вершині " << Find(to_sort, sorted[i], m) << endl;
                        }
                        system("pause");
                        for (int i = 0; i < m; i++)
                        {
                            sorted[i] = to_sort[i];
                        }
                        break;
                    }
                    }
                } while (ans != 6);
                delete[] to_sort;
                delete[] sorted;
            }
            else
            {
                cout << "Некоректний ввід графу" << endl;
                system("pause");
            }
            break;
        }
        case 3:
        {
            int i = 1;
            FILE* fp = fopen("Graph.dat", "rb");
            fseek(fp, 0, SEEK_SET);
            fread(&m, sizeof(int), 1, fp);
            Graph graph;
            fseek(fp, sizeof(int), SEEK_SET);
            fread(&graph, sizeof(int) + sizeof(Graph), 1, fp);
            Graph* pbeg = first(graph.ver_1, graph.ver_2);
            Graph* pend = pbeg;
            while (true)
            {
                Graph graph;
                fseek(fp, sizeof(int) + (sizeof(Graph)) * i, SEEK_SET);
                fread(&graph, sizeof(Graph), 1, fp);
                if (feof(fp)) break;
                add(&pend, graph.ver_1, graph.ver_2);
                i++;
            }
            fclose(fp);

            Graph* p = pbeg;
            mas = new int* [m];
            for (int i = 0; i < m; i++)
            {
                mas[i] = new int[m];
                for (int j = 0; j < m; j++)
                {
                    if (p != nullptr)
                    {
                        if ((p->ver_1 == i + 1) && (p->ver_2 == j + 1))
                        {
                            mas[i][j] = 1;
                            p = p->next;
                        }
                        else mas[i][j] = 0;
                    }
                    else mas[i][j] = 0;
                }
            }

            break;
        }
        case 4:
        {
            exit(0);
        }
        }
    } while (answer != 4);

    delete[] mas;

    return 0;
}
