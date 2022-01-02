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

void GetMatr(int** mas, int** p, int i, int j, int m)
{
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++)
    {
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++)
        {
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

int Determinant(int** mas, int m)
{
    int i, j, d, k, n;
    int** p;
    p = new int* [m];
    for (i = 0; i < m; i++)
        p[i] = new int[m];
    j = 0; d = 0;
    k = 1;
    n = m - 1;
    if (m == 1)
    {
        d = mas[0][0];
        return(d);
    }
    if (m == 2)
    {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
    }
    if (m > 2)
    {
        for (i = 0; i < m; i++)
        {
            GetMatr(mas, p, i, 0, m);
            d = d + k * mas[i][0] * Determinant(p, n);
            k = -k;
        }
    }
    return(d);
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
        if (key == 2) cout << "-> Підрахувати визначник" << endl;
        else  cout << "   Підрахувати визначник" << endl;
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

int main()
{
    SetConsoleOutputCP(1251);
    int m = 0, d;
    int** mas;
    mas = new int* [1];
    int answer;
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
                        add(&pend, i+1, j+1);
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
                d = Determinant(mas, m);
                cout << "Визначник матриці дорівнює: " << d << endl;
                system("pause");
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

    return 0;
}