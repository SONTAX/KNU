#include "Header.h"

int main()
{
	SetConsoleOutputCP(1251);
	long long n = 0;
	while (n <= 0 || n > 32)
	{
		cout << "Введіть кількість змінних (до 32): ";
		while (!(cin >> n) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Некорекиний ввід даних! Спробуйте знову: ";
		}
		cin.clear();
		if (n <= 0 || n > 32) cout << "Кількість змінних не може бути менше 1, або більше 32!" << endl;
	}

	bool work = false;
	POLINOM a;
	while (!work)
	{
		system("cls");

		cout << "Кількість змінних: " << n << endl;

		cout << endl;

		a.print();

		cout << endl;

		Info X;
		while ((X.num <= 0 || X.num > n) && !work)
		{
			cout << "Введіть номер змінної (1 - " << n << "), або 0 якщо хочете завершити Поліном: ";
			while (!(cin >> X.num) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Некорекиний ввід даних! Спробуйте знову: ";
			}
			if (X.num == 0) work = true;
			else if (X.num <= 0 || X.num > n) cout << "Змінної з данним номером не існує!" << endl;
		}
		if (work) break;

		cout << "Введіть [1], якщо ви хочете виконати операцію диз'юнкції над наступною змінною або [0], якщо ви хочете виконати операцію суми по модулю 2: ";
		while (!(cin >> X.oper_next) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Некорекиний ввід даних! Спробуйте знову: ";
		}

		a.add(X);
	}

	system("cls");

	a.print();
	cout << endl;

	DNF b;

	for (long long i = 0; i < pow(2, n); i++)
	{
		if (a.f(i))
		{
			for (long long j = 0; j < n; j++)
			{
				Info Y;
				Y.num = n - j;
				if ((i >> (n - j - 1)) % 2)
				{
					Y.inv = 0;
				}
				else
				{
					Y.inv = 1;
				}
				if (j == n - 1) Y.oper_next = 1;
				else Y.oper_next = 0;
				b.add(Y);
			}
		}
	}

	cout << endl;
	b.print();

	cout << endl;

	cout << endl << "    ";
	for (long long i = 0; i <= n; i++)
	{
		if (i == n) cout << "|    f" << endl << "____";
		else
		{
			cout << "x" << n - i;
			if ((n - i) / 10 == 0) cout << "   ";
			else cout << "  ";
		}

	}
	for (long long i = 0; i < n; i++)
	{
		cout << "_____";
	}
	cout << "________";
	cout << endl;
	for (long long i = 0; i < pow(2, n); i++)
	{
		cout << endl;
		for (long long j = 0; j < n; j++)
		{
			cout << "    " << (i >> (n - j - 1)) % 2;
		}
		cout << "    |    " << a.f(i) << endl;
	}
	cout << "____";
	for (long long i = 0; i <= n; i++)
	{
		cout << "_____";
	}
	cout << "___";
	cout << endl;
	return 0;
}