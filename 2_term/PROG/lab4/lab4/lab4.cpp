#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <cstring>
#include <cmath>

using namespace std;

struct Node
{
	char data[40];
	Node* left, * right;
};
typedef Node* PNode;

int Priority(char c)
{
	switch (c)
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^': return 3;
	case 'S': case 'C': return 4;
	}
	return 100;
}

PNode MakeTree(char Expr[], int first, int last)
{
	int nest = 0;
	int MinPrt, i, k, prt;
	PNode Tree = new Node;
	MinPrt = 100;
	for (i = first; i <= last; i++)
	{
		if (Expr[i] == '(')
		{
			nest++; continue;
		}
		if (Expr[i] == ')')
		{
			nest--; continue;
		}
		if (nest > 0) continue;
		prt = Priority(Expr[i]);
		if (prt <= MinPrt) {
			MinPrt = prt;
			k = i;
		}
	}
	if (MinPrt == 100)
		if (Expr[first] == '(' && Expr[last] == ')')
		{
			delete Tree;
			return MakeTree(Expr, first + 1, last - 1);
		}
		else
		{
			k = last - first + 1;
			strncpy(Tree->data, Expr + first, k);
			Tree->data[k] = '\0';
			Tree->left = NULL;
			Tree->right = NULL;
			return Tree;
		}
	Tree->data[0] = Expr[k];
	Tree->data[1] = '\0';
	Tree->left = MakeTree(Expr, first, k - 1);
	Tree->right = MakeTree(Expr, k + 1, last);
	return Tree;
}

double CalcTree(PNode Tree)
{
	double num1, num2;
	if (!Tree->left)
	{
		if (((Tree->data[0] >= 'a') || (Tree->data[0] >= 'A')) && ((Tree->data[0] <= 'z') || (Tree->data[0] <= 'Z')))
		{
			cout << "Уведіть значення змінної " << Tree->data << " > ";
			cin >> Tree->data;
		}
		return atof(Tree->data);
	}
	num1 = CalcTree(Tree->left);
	num2 = CalcTree(Tree->right);
	switch (Tree->data[0])
	{
	case '+': return (num1 + num2);
	case '-': return (num1 - num2);
	case '*': return (num1 * num2);
	case '/': return (num1 / num2);
	case '^': return pow(num1, num2);
	case 'C': return cos(num2);
	case 'S': return sin(num2);
	}
	return 32767;
}

int main()
{
	SetConsoleOutputCP(1251);
	char s[1000];
	PNode Tree;
	cout << "Змінні та дійсні числа" << endl;
	cout << "Доступні операції: '+', '-', '^', '*', '/', 'sin', 'cos', унарний мінус" << endl << endl;
	cout << "Уведіть вираз > ";
	gets_s(s);
	char* S = new char[strlen(s)];
	int k = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if ((s[k] == 's') && (s[k + 1] == 'i') && (s[k + 2] == 'n'))
		{
			S[i] = 'S';
			k += 3;
		}
		else if ((s[k] == 'c') && (s[k + 1] == 'o') && (s[k + 2] == 's'))
		{
			S[i] = 'C';
			k += 3;
		}
		else if (i <= k)
		{
			S[i] = s[k];
			k++;
		}
		else S[i] = '\0';
	}
	Tree = MakeTree(s, 0, strlen(s) - 1);
	cout << endl << "Результат виразу > " << CalcTree(Tree) << endl;
	return 0;
}