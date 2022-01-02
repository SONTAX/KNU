#pragma once

#include <iostream>
#include <windows.h>
#include "Header.h"

using namespace std;

struct Info
{
	int num = 0;
	bool x;
	bool oper_prev; // (1 - |), (0 - &)
	bool oper_next;
	bool inv;
};

struct Elem
{
	Info about;
	Elem* next = nullptr;
	Elem* prev = nullptr;
};

struct POLINOM
{
	Elem* head = nullptr;
	Elem* tail = nullptr;
	void add(Info& new_elem)
	{
		Elem* add_elem = new Elem;
		if (tail == nullptr)
		{
			new_elem.oper_prev = 1;
		}
		else
		{
			new_elem.oper_prev = tail->about.oper_next;
		}
		add_elem->about = new_elem;
		if (head == nullptr)
		{
			head = add_elem;
			tail = add_elem;
		}
		else
		{
			tail->next = add_elem;
			add_elem->prev = tail;
			tail = add_elem;
		}
	}
	void print()
	{
		Elem* current = head;
		cout << "Ïîë³íîì Æåãàëê³íà: ";
		if (current == nullptr)
		{
			cout << "0" << endl;
		}
		else
		{
			while (current != nullptr)
			{
				if (current->prev == nullptr) cout << "x" << current->about.num;
				else
				{
					if (current->about.oper_prev)cout << "*" << "x" << current->about.num;
					else cout << " + " << "x" << current->about.num;
				}
				current = current->next;
			}
		}
	}
	bool f(long long i)
	{
		Elem* current = head;
		bool func = 0;
		bool func1 = 0;
		while (current != nullptr)
		{
			current->about.x = (i >> ((current->about.num) - 1)) % 2;
			if (current == head) func1 = func1 | current->about.x;
			else
			{
				if (current->about.oper_prev) func1 = func1 & current->about.x;
				else func1 = func1 ^ current->about.x;
			}
			if ((!current->about.oper_next) || current->next == nullptr)
			{
				func = func ^ func1;
				func1 = 0;
			}
			current = current->next;
		}
		return func;
	}
};

struct DNF
{
	Elem* head = nullptr;
	Elem* tail = nullptr;
	void add(Info& new_elem)
	{
		Elem* add_elem = new Elem;
		if (tail == nullptr)
		{
			new_elem.oper_prev = 1;
		}
		else
		{
			new_elem.oper_prev = tail->about.oper_next;
		}
		add_elem->about = new_elem;
		if (head == nullptr)
		{
			head = add_elem;
			tail = add_elem;
		}
		else
		{
			tail->next = add_elem;
			add_elem->prev = tail;
			tail = add_elem;
		}
	}
	void print()
	{
		Elem* current = head;
		cout << "ÄÍÔ: ";
		if (current == nullptr)
		{
			cout << "0" << endl;
		}
		else
		{
			while (current != nullptr)
			{
				if (current->prev == nullptr)
				{
					if (current->about.inv)
					{
						cout << "(!x" << current->about.num << ")";
					}
					else
					{
						cout << "x" << current->about.num;
					}
				}
				else
				{
					if (current->about.inv)
					{
						if (current->about.oper_prev)
						{
							cout << " ^ " << "(!x" << current->about.num << ")";
						}
						else
						{
							cout << "*" << "(!x" << current->about.num << ")";
						}
					}
					else
					{
						if (current->about.oper_prev)
						{
							cout << " ^ " << "x" << current->about.num;
						}
						else
						{
							cout << "*" << "x" << current->about.num;
						}
					}
				}
				current = current->next;
			}
		}
	}
};