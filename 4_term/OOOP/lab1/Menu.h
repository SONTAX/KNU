#ifndef MENU_H_
#define MENU_H_

#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int enter_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "Choose mode:" << endl;
		key = (key + 3) % 3;
		if (key == 0) cout << "-> Demonstration" << endl;
		else  cout << "   Demonstration" << endl;
		if (key == 1) cout << "-> Interactive" << endl;
		else  cout << "   Interactive" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Date and time" << endl;
		else  cout << "   Date and time" << endl;
		if (key == 1) cout << "-> Matrix" << endl;
		else  cout << "   Matrix" << endl;
		if (key == 2) cout << "-> List" << endl;
		else  cout << "   List" << endl;
		if (key == 3) cout << "-> Tree" << endl;
		else  cout << "   Tree" << endl;
		if (key == 4) cout << "-> Back" << endl;
		else  cout << "   Back" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int matrix_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 10) % 10;
		if (key == 0) cout << "-> Generate new matrix" << endl;
		else  cout << "   Generate new matrix" << endl;
		if (key == 1) cout << "-> Input matrix" << endl;
		else  cout << "   Input matrix" << endl;
		if (key == 2) cout << "-> Print matrix" << endl;
		else  cout << "   Print matrix" << endl;
		if (key == 3) cout << "-> Summation (with random matrix)" << endl;
		else  cout << "   Summation (with random matrix)" << endl;
		if (key == 4) cout << "-> Multiplication (by random matrix)" << endl;
		else  cout << "   Multiplication (by random matrix)" << endl;
		if (key == 5) cout << "-> Multiplication (by random vector)" << endl;
		else  cout << "   Multiplication (by random vector)" << endl;
		if (key == 6) cout << "-> Transposition" << endl;
		else  cout << "   Transposition" << endl;
		if (key == 7) cout << "-> Get value by indexes" << endl;
		else  cout << "   Get value by indexes" << endl;
		if (key == 8) cout << "-> Get indexes by value" << endl;
		else  cout << "   Get indexes by value" << endl;
		if (key == 9) cout << "-> Back" << endl;
		else  cout << "   Back" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int date_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0) cout << "-> Input new full date" << endl;
		else  cout << "   Input new full date" << endl;
		if (key == 1) cout << "-> Arithmetic operations with dates" << endl;
		else  cout << "   Arithmetic operations with dates" << endl;
		if (key == 2) cout << "-> Day of the week" << endl;
		else  cout << "   Day of the week" << endl;
		if (key == 3) cout << "-> Print" << endl;
		else  cout << "   Print" << endl;
		if (key == 4) cout << "-> Difference between dates" << endl;
		else  cout << "   Difference between dates" << endl;
		if (key == 5) cout << "-> Back" << endl;
		else  cout << "   Back" << endl;
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
int difference_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 2) % 2;
		if (key == 0) cout << "-> Take away from" << endl;
		else  cout << "   Take away from" << endl;
		if (key == 1) cout << "-> Add to" << endl;
		else  cout << "   Add to" << endl;
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
int binary_tree_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 11) % 11;
		if (key == 0) cout << "-> Print tree as list" << endl;
		else  cout << "   Print tree as list" << endl;
		if (key == 1) cout << "-> Print tree as tree" << endl;
		else  cout << "   Print tree as tree" << endl;
		if (key == 2) cout << "-> New binary tree" << endl;
		else  cout << "   New binary tree" << endl;
		if (key == 3) cout << "-> New random binary tree" << endl;
		else  cout << "   New random binary tree" << endl;
		if (key == 4) cout << "-> New BST" << endl;
		else  cout << "   New BST" << endl;
		if (key == 5) cout << "-> New random BST" << endl;
		else  cout << "   New random BST" << endl;
		if (key == 6) cout << "-> Add new node to tree (as for BST)" << endl;
		else  cout << "   Add new node to tree (as for BST)" << endl;
		if (key == 7) cout << "-> Delete by value" << endl;
		else  cout << "   Delete by value" << endl;
		if (key == 8) cout << "-> Delete by parent node (You need to do 'Find' first)" << endl;
		else  cout << "   Delete by parent node (You need to do 'Find' first)" << endl;
		if (key == 9) cout << "-> Find value" << endl;
		else  cout << "   Find value" << endl;
		if (key == 10) cout << "-> Back" << endl;
		else  cout << "   Back" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int list_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 7) % 7;
		if (key == 0) cout << "-> Add new node" << endl;
		else  cout << "   Add new node" << endl;
		if (key == 1) cout << "-> Input new list" << endl;
		else  cout << "   Input new list" << endl;
		if (key == 2) cout << "-> Get new random list" << endl;
		else  cout << "   Get new random list" << endl;
		if (key == 3) cout << "-> Print" << endl;
		else  cout << "   Print" << endl;
		if (key == 4) cout << "-> Get value by index" << endl;
		else  cout << "   Get value by index" << endl;
		if (key == 5) cout << "-> Get index by value" << endl;
		else  cout << "   Get index by value" << endl;
		if (key == 6) cout << "-> Back" << endl;
		else  cout << "   Back" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}
int date_choice_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 2) % 2;
		if (key == 0) cout << "-> First date" << endl;
		else  cout << "   First date" << endl;
		if (key == 1) cout << "-> Second date" << endl;
		else  cout << "   Second date" << endl;
		code = _getch();
		if (code == 224) {
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

#endif