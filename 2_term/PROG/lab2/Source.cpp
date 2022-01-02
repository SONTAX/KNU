#include "Header.h"

int main()
{
	SetConsoleOutputCP(1251);
	long long n = 0;
	while (n <= 0 || n > 32)
	{
		cout << "������ ������� ������ (�� 32): ";
		while (!(cin >> n) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ��� �����! ��������� �����: ";
		}
		cin.clear();
		if (n <= 0 || n > 32) cout << "ʳ������ ������ �� ���� ���� ����� 1, ��� ����� 32!" << endl;
	}

	bool work = false;
	POLINOM a;
	while (!work)
	{
		system("cls");

		cout << "ʳ������ ������: " << n << endl;

		cout << endl;

		a.print();

		cout << endl;

		Info X;
		while ((X.num <= 0 || X.num > n) && !work)
		{
			cout << "������ ����� ����� (1 - " << n << "), ��� 0 ���� ������ ��������� ������: ";
			while (!(cin >> X.num) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "����������� ��� �����! ��������� �����: ";
			}
			if (X.num == 0) work = true;
			else if (X.num <= 0 || X.num > n) cout << "����� � ������ ������� �� ����!" << endl;
		}
		if (work) break;

		cout << "������ [1], ���� �� ������ �������� �������� ���'������ ��� ��������� ������ ��� [0], ���� �� ������ �������� �������� ���� �� ������ 2: ";
		while (!(cin >> X.oper_next) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ��� �����! ��������� �����: ";
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