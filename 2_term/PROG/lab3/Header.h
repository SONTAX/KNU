#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 100;

struct Matrix
{
    vector<int> val;
    vector<int> row;
    vector<int> col;
};

void Show(Matrix* A)
{
    int k = 0;
    int size = A->col.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (k < size)
            {
                if ((A->row[k] == i) && (A->col[k] == j)) cout << A->val[k++] << " ";
                else cout << "0" << " ";
            }
            else cout << "0" << " ";
        }
        cout << endl;
    }
}

void Get(Matrix* A)
{
    A->col.clear();
    A->row.clear();
    A->val.clear();
    int input;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> input;
            if (input != 0)
            {
                A->val.push_back(input);
                A->col.push_back(j);
                A->row.push_back(i);
            }
        }
    }
}

void GetRnd(Matrix* A)
{
    A->col.clear();
    A->row.clear();
    A->val.clear();
    int input;
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input = rand() % 3;
            if (input != 0)
            {
                A->val.push_back(input);
                A->col.push_back(j);
                A->row.push_back(i);
            }
        }
    }
}

void Sum(Matrix* A, Matrix* B)
{
    int ka = 0;
    int kb = 0;
    int size_a = A->col.size();
    int size_b = B->col.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((ka < size_a) && (kb < size_b))
            {
                if ((A->col[ka] == B->col[kb]) && (B->col[kb] == j) && (A->row[ka] == B->row[kb]) && (B->row[kb] == i)) cout << A->val[ka++] + B->val[kb++] << " ";
                else if ((A->col[ka] == j) && (A->row[ka] == i)) cout << A->val[ka++] << " ";
                else if ((B->col[kb] == j) && (B->row[kb] == i)) cout << B->val[kb++] << " ";
                else cout << "0" << " ";
            }
            else if ((ka < size_a) && (kb == size_b))
            {
                if ((A->col[ka] == j) && (A->row[ka] == i)) cout << A->val[ka++] << " ";
                else cout << "0" << " ";
            }
            else if ((ka == size_a) && (kb < size_b))
            {
                if ((B->col[kb] == j) && (B->row[kb] == i)) cout << B->val[kb++] << " ";
                else cout << "0" << " ";
            }
            else cout << "0" << " ";
        }
        cout << endl;
    }
}

void Comp(Matrix* A, Matrix* B)
{
    int ka = 0;
    int size_a = A->col.size();
    int a[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) a[i][j] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (ka < size_a)
            {
                if ((A->row[ka] == i) && (A->col[ka] == j)) a[i][j] = A->val[ka++];
            }
        }
    }
    int kb = 0;
    int size_b = B->col.size();
    int b[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) b[i][j] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (kb < size_b)
            {
                if ((B->row[kb] == i) && (B->col[kb] == j)) b[i][j] = B->val[kb++];
            }
        }
    }
    int c[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for (int p = 0; p < n; p++) {
                c[i][j] += a[i][p] * b[p][j];
            }
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
}

int menu()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 12) % 12;
        if (key == 0) cout << "-> Увести матрицю А з клавіатури та зберегти у файл" << endl;
        else  cout << "   Увести матрицю А з клавіатури та зберегти у файл" << endl;
        if (key == 1) cout << "-> Увести матрицю А з файлу" << endl;
        else  cout << "   Увести матрицю А з файлу" << endl;
        if (key == 2) cout << "-> Увести матрицю В з клавіатури та зберегти у файл" << endl;
        else  cout << "   Увести матрицю В з клавіатури та зберегти у файл" << endl;
        if (key == 3) cout << "-> Увести матрицю В з файлу" << endl;
        else  cout << "   Увести матрицю В з файлу" << endl;
        if (key == 4) cout << "-> Вивести матрицю А" << endl;
        else  cout << "   Вивести матрицю А" << endl;
        if (key == 5) cout << "-> Вивести матрицю В" << endl;
        else  cout << "   Вивести матрицю В" << endl;
        if (key == 6) cout << "-> Додати матриці А та В" << endl;
        else  cout << "   Додати матриці А та В" << endl;
        if (key == 7) cout << "-> Помножити матрицю А на В" << endl;
        else  cout << "   Помножити матрицю А на В" << endl;
        if (key == 8) cout << "-> Помножити матрицю В на А" << endl;
        else  cout << "   Помножити матрицю В на А" << endl;
        if (key == 9) cout << "-> Заповнити випадковими числами (0-2) матрицю А" << endl;
        else  cout << "   Заповнити випадковими числами (0-2) матрицю А" << endl;
        if (key == 10) cout << "-> Заповнити випадковими числами (0-2) матрицю В" << endl;
        else  cout << "   Заповнити випадковими числами (0-2) матрицю В" << endl;
        if (key == 11) cout << "-> Завершити роботу" << endl;
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