#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

class Day {
public:
	int value;
	explicit Day(int new_value) {
		value = new_value;
	}
};
class Month {
public:
	int value;
	explicit Month(int new_value) {
		value = new_value;
	}
};
class Year {
public:
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};
class Hour {
public:
	int value;
	explicit Hour(int new_value) {
		value = new_value;
	}
};
class Minute {
public:
	int value;
	explicit Minute(int new_value) {
		value = new_value;
	}
};
class Second {
public:
	int value;
	explicit Second(int new_value) {
		value = new_value;
	}
};
class Full_Date {
public:

	Full_Date(Year new_year, Month new_month, Day new_day, Hour new_hour, Minute new_minute, Second new_second) {
		day = new_day.value;
		month = new_month.value;
		year = new_year.value;
		hour = new_hour.value;
		minute = new_minute.value;
		second = new_second.value;
		IsYearLeap();
	}
	Full_Date() {};

	void Fill() {
		string input;
		cout << "Input date (format: yyyy.mm.dd): ";
		cin >> input;
		bool correct_input = TransformStringIntoDate(input);
		if (!correct_input) {
			system("cls");
			cout << "Incorrect input!\nPlease, try again!\n\n";
			Fill();
			return;
		}
		cout << "Input time (format: hh:mm:ss): ";
		cin >> input;
		correct_input = TransformStringIntoTime(input);
		IsYearLeap();
		correct_input = IsInputedDataCorrect();
		if (!correct_input) {
			system("cls");
			cout << "Incorrect input!\nPlease, try again!\n\n";
			Fill();
			return;
		}
	}

	void DateDifference(Full_Date date_2) {
		Full_Date date_1 = { Year(year),Month(month),Day(day),Hour(hour),Minute(minute),Second(second) };
		int JDN_1 = date_1.GetJDN();
		int JDN_2 = date_2.GetJDN();
		int SEC_1 = date_1.GetTimeInSeconds();
		int SEC_2 = date_2.GetTimeInSeconds();
		days_difference = JDN_1 - JDN_2;
		seconds_difference = SEC_1 - SEC_2;
		if ((days_difference > 0) && (seconds_difference < 0)) {
			seconds_difference += 86400;
			days_difference--;
		}
		else if ((days_difference < 0) && (seconds_difference > 0)) {
			days_difference++;
			seconds_difference = 86400 - seconds_difference;
		}
		seconds_difference = abs(seconds_difference);
		days_difference = abs(days_difference);
	}

	void Arithmetic(int sign) {
		int JDN = GetJDN();
		int seconds = GetTimeInSeconds();
		cout << "Difference is " << days_difference << " days and " << seconds_difference << " seconds" << endl;
		if (sign) {
			JDN += days_difference;
			seconds += seconds_difference;
		}
		else {
			JDN -= days_difference;
			seconds -= seconds_difference;
		}
		ReverseJDN(JDN);
		if (seconds > 86399) {
			seconds = seconds - 86400;
			day++;
		}
		else if (seconds < 0) {
			seconds = 86400 + seconds;
			day--;
		}
		ReverseSeconds(seconds);
		bool correct_input = IsInputedDataCorrect();
		if (!correct_input) {
			system("cls");
			cout << "Derived date is out of date year range(-2000 - 4000)\nPlease, input new correct date, if you want to continue!\n\n";
			Fill();
			return;
		}
	}

	void DayOfTheWeek() {
		int day_in_number = GetJDN() % 7;
		switch (day_in_number) {
		case 0: {
			cout << "Monday" << endl;
			break;
		}
		case 1: {
			cout << "Tuesday" << endl;
			break;
		}
		case 2: {
			cout << "Wednesday" << endl;
			break;
		}
		case 3: {
			cout << "Thursday" << endl;
			break;
		}
		case 4: {
			cout << "Friday" << endl;
			break;
		}
		case 5: {
			cout << "Saturday" << endl;
			break;
		}
		case 6: {
			cout << "Sunday" << endl;
			break;
		}
		}
	}

	void Print() {
		cout << year << "." << month << "." << day << " " << hour << ":" << minute << ":" << second << endl;
	}

	void GetDif() {
		cout << days_difference << " " << seconds_difference << endl;
		system("pause");
	}

private:

	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	int GetJDN() const {
		int result;
		int d = (14 - month) / 12;
		int m = month + 12 * d - 3;
		int y = year + 4800 - d;
		result = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
		return result;
	}
	int GetTimeInSeconds() const {
		int result;
		result = hour * 3600 + minute * 60 + second;
		return result;
	}

	void ReverseJDN(int JDN) {
		int a = JDN + 32044;
		int b = (4 * a + 3) / 146097;
		int c = a - (146097 * b) / 4;
		int d = (4 * c + 3) / 1461;
		int e = c - (1461 * d) / 4;
		int m = (5 * e + 2) / 153;
		day = e - (153 * m + 2) / 5 + 1;
		month = m + 3 - 12 * (m / 10);
		year = 100 * b + d - 4800 + (m / 10);
	}
	void ReverseSeconds(int seconds) {
		hour = seconds / 3600;
		minute = (seconds % 3600) / 60;
		second = (seconds % 3600) % 60;
	}

	void IsYearLeap() {
		if (!(year % 4 != 0 || year % 100 == 0 && year % 400 != 0)) {
			is_year_leap = true;
			days_in_month[1]++;
		}
	}
	bool IsInputedDataCorrect() {
		if (((year < -2000) || (year == 0) || (year > 4000)) || ((month < 1) || (month > 12)) || ((day < 1) || (day > days_in_month[month - 1])) || ((hour < 0) || (hour > 23)) || ((minute < 0) || (minute > 59)) || ((second < 0) || (second > 59))) {
			return false;
		}
		return true;
	}
	bool TransformStringIntoDate(string input) {
		string transform;
		for (size_t i = 0, counter = 0; i <= input.size(); i++) {
			if (input[i] == '.') {
				counter++;
				if (counter == 1) {
					year = stoi(transform);
				}
				else if (counter == 2) {
					month = stoi(transform);
				}
				else {
					return false;
				}
				transform.clear();
			}
			else if (i == input.size()) {
				day = stoi(transform);
			}
			else {
				transform += input[i];
			}
		}
		return true;
	}
	bool TransformStringIntoTime(string input) {
		string transform; for (size_t i = 0, counter = 0; i <= input.size(); i++) {
			if (input[i] == ':') {
				counter++;
				if (counter == 1) {
					hour = stoi(transform);
				}
				else if (counter == 2) {
					minute = stoi(transform);
				}
				else {
					return false;
				}
				transform.clear();
			}
			else if (i == input.size()) {
				second = stoi(transform);
			}
			else {
				transform += input[i];
			}
		}
		return true;
	}

	int days_difference;
	int seconds_difference;
	vector<int> days_in_month = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool is_year_leap = false;
};

struct Matrix {

	vector<int> val;
	vector<int> row;
	vector<int> col;
	int dimension;

	bool was_zero = false;
	int zero_row;
	int zero_col;

	void PrintMatrix() const {
		int k = 0;
		int size = col.size();
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if (k < size) {
					if ((row[k] == i) && (col[k] == j)) cout << val[k++] << " ";
					else cout << "0" << " ";
				}
				else cout << "0" << " ";
			}
			cout << endl;
		}
	}
	void GetMatrix(int n) {
		col.clear();
		row.clear();
		val.clear();
		int input;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> input;
				if (input != 0)
				{
					val.push_back(input);
					row.push_back(i);
					col.push_back(j);
				}
				if (!was_zero) {
					if (input == 0) {
						was_zero = true;
						zero_col = j;
						zero_row = i;
					}
				}
			}
		}
		dimension = n;
	}
	void GetRandomMatrix(int n) {
		col.clear();
		row.clear();
		val.clear();
		int input;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				input = rand() % 5;
				if (input != 0)
				{
					val.push_back(input);
					col.push_back(j);
					row.push_back(i);
				}
				if (!was_zero) {
					if (input == 0) {
						was_zero = true;
						zero_col = j;
						zero_row = i;
					}
				}
			}
		}
		dimension = n;
	}
	void GetByIndex(int rw, int cl) {
		rw--;
		cl--;
		if ((rw <= dimension) && (cl <= dimension)) {
			for (int i = 0; i < val.size(); i++) {
				if ((row[i] == rw) && (col[i] == cl)) {
					cout << "Value: " << val[i] << endl;
					return;
				}
			}
			cout << "Value: 0" << endl;
		}
		else {
			cout << "Indexes are more then dimension!" << endl;
		}
	}
	void GetByValue(int value) {
		if (value != 0) {
			for (size_t i = 0; i < val.size(); i++) {
				if (val[i] == value) {
					cout << "Row: " << row[i] + 1 << endl << "Column: " << col[i] + 1 << endl;
					return;
				}
			}
			cout << "There are no indexes for such value!" << endl;
		}
		else {
			cout << "Row: " << zero_row + 1 << endl << "Column: " << zero_col + 1 << endl;
		}
	}
	void Sum() {
		Matrix A;
		A.val = val;
		A.col = col;
		A.row = row;
		Matrix B;
		B.GetRandomMatrix(dimension);
		int ka = 0;
		int kb = 0;
		int size_a = A.col.size();
		int size_b = B.col.size();
		cout << "MATRIX A" << endl;
		PrintMatrix();
		cout << "MATRIX B" << endl;
		B.PrintMatrix();
		cout << endl << "MATRIX SUMMARY" << endl << endl;
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if ((ka < size_a) && (kb < size_b)) {
					if ((A.col[ka] == B.col[kb]) && (B.col[kb] == j) && (A.row[ka] == B.row[kb]) && (B.row[kb] == i)) { 
						cout << A.val[ka++] + B.val[kb++] << " "; 
					}
					else if ((A.col[ka] == j) && (A.row[ka] == i)) {
						cout << A.val[ka++] << " ";
					}
					else if ((B.col[kb] == j) && (B.row[kb] == i)) {
						cout << B.val[kb++] << " ";
					}
					else {
						cout << "0" << " ";
					}
				}
				else if ((ka < size_a) && (kb == size_b)) {
					if ((A.col[ka] == j) && (A.row[ka] == i)) {
						cout << A.val[ka++] << " ";
					}
					else {
						cout << "0" << " ";
					}
				}
				else if ((ka == size_a) && (kb < size_b)) {
					if ((B.col[kb] == j) && (B.row[kb] == i)) {
						cout << B.val[kb++] << " ";
					}
					else {
						cout << "0" << " ";
					}
				}
				else {
					cout << "0" << " ";
				}
			}
			cout << endl;
		}
	}
	void MultiplicationByMatrix() {
		Matrix A;
		A.val = val;
		A.col = col;
		A.row = row;
		Matrix B;
		B.GetRandomMatrix(dimension);
		cout << "MATRIX A" << endl;
		PrintMatrix();
		cout << "MATRIX B" << endl;
		B.PrintMatrix();
		cout << endl << "MATRIX MULTIPLICATION" << endl << endl;
		int ka = 0;
		int size_a = A.col.size();
		int kb = 0;
		int size_b = B.col.size();
		int** a = new int* [dimension];
		int** b = new int* [dimension];
		int** c = new int* [dimension];
		for (int i = 0; i < dimension; i++) {
			a[i] = new int[dimension];
			b[i] = new int[dimension];
			c[i] = new int[dimension];
			for (int j = 0; j < dimension; j++) {
				a[i][j] = 0;
				b[i][j] = 0;
				c[i][j] = 0;
			}
		}
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if (kb < size_b) {
					if ((B.row[kb] == i) && (B.col[kb] == j)) b[i][j] = B.val[kb++];
				}
				if (ka < size_a) {
					if ((A.row[ka] == i) && (A.col[ka] == j)) a[i][j] = A.val[ka++];
				}
			}
		}
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				for (int p = 0; p < dimension; p++) {
					c[i][j] += a[i][p] * b[p][j];
				}
				cout << c[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < dimension; i++) {
			delete[] a[i];
			delete[] b[i];
			delete[] c[i];
		}
		delete[] a;
		delete[] b;
		delete[] c;
	}
	void MultiplicationByVector() {
		int ka = 0;
		int size_a = col.size();
		int** a = new int* [dimension];
		cout << "MATRIX A" << endl;
		PrintMatrix();
		vector<int> b;
		b.resize(dimension);
		vector<int> c;
		c.resize(dimension);
		cout << "VECTOR B" << endl;
		for (size_t i = 0; i < dimension; i++) {
			a[i] = new int[dimension];
			b[i] = rand() % 5;
			c[i] = 0;
			for (size_t j = 0; j < dimension; j++) {
				a[i][j] = 0;
				if (ka < size_a) {
					if ((row[ka] == i) && (col[ka] == j)) a[i][j] = val[ka++];
				}
			}
			cout << b[i] << " ";
		}
		cout << endl << "RESULT" << endl;
		for (size_t i = 0; i < dimension; i++) {
			for (size_t j = 0; j < dimension; j++) {
				c[i] += a[i][j] * b[j];
			}
			cout << c[i] << " ";
		}
		cout << endl;
		for (size_t i = 0; i < dimension; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
	void Transponation() {
		int k = 0;
		int** T = new int* [dimension];
		for (size_t i = 0; i < dimension; i++) {
			T[i] = new int[dimension];
			for (size_t j = 0; j < dimension; j++) T[i][j] = 0;
		}
		for (size_t i = 0; i < val.size(); i++) {
			T[col[i]][row[i]] = val[i];
		}
		for (size_t i = 0; i < dimension; i++) {
			for (size_t j = 0; j < dimension; j++) {
				cout << T[i][j] << " ";
			}
			cout << endl;
		}
		for (size_t i = 0; i < dimension; i++) delete[] T[i];
		delete[] T;
	}
};

template<typename T>
struct Node {
	size_t index;
	T value;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;
};
template<typename T>
struct SparseList {
	Node<T>* pbeg = nullptr;
	Node<T>* pend = nullptr;
	size_t list_size = 0;

	bool was_zero = false;
	size_t zero_index;

	void Add(T val) {
		if (val) {
			Node<T>* new_node = new Node<T>;
			new_node->value = val;
			new_node->index = list_size;
			if (pbeg == nullptr) {
				pbeg = new_node;
				pend = new_node;
			}
			else {
				new_node->prev = pend;
				pend->next = new_node;
				pend = new_node;
			}
		}
		if (!was_zero) {
			if (val == 0) {
				was_zero = true;
				zero_index = list_size;
			}
		}
		list_size++;
	}
	void PrintAll() {
		Node<T>* current = pbeg;
		for (size_t i = 0; i < list_size; i++) {
			if (current) {
				if (i == current->index) {
					cout << current->value << " ";
					current = current->next;
				}
				else {
					cout << "0 ";
				}
			}
			else {
				cout << "0 ";
			}
		}
	}
	void GetList(size_t lenth) {
		DeleteList();
		int input;
		for (size_t i = 0; i < lenth; i++) {
			cin >> input;
			Add(input);
		}
	}
	void GetIndex(T val) {
		if (val != 0) {
			Node<T>* current = pbeg;
			while (current) {
				if (current->value == val) {
					cout << "Index for this value is: " << current->index << endl;
					return;
				}
				current = current->next;
			}
			cout << "There is no index for such value!" << endl;
		}
		else {
			cout << "Index for this value is: " << zero_index << endl;
		}
	}
	void GetValue(size_t ind) {
		if (ind < list_size) {
			Node<T>* current = pbeg;
			while (current) {
				if (current->index == ind) {
					cout << "Value for this index is: " << current->value << endl;
					return;
				}
				current = current->next;
			}
			cout << "Value for this index is: 0" << endl;
		}
		else {
			cout << "This index is larger then list max index: " << list_size - 1 << "!" << endl;
		}
	}
	void GetRandomList(size_t lenth) {
		DeleteList();
		T val;
		for (size_t i = 0; i < lenth; i++) {
			val = (rand() % 16) / 3;
			Add(val);
		}
	}
	void DeleteList() {
		Node<T>* current = pbeg;
		while (current) {
			Node<T>* del = current;
			current = current->next;
			delete del;
		}
		pbeg = nullptr;
		pend = nullptr;
		list_size = 0;
	}
};

template<typename T>
struct TreeNode {
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;
};
template<typename T>
struct Tree {
	TreeNode<T>* root;
	TreeNode<T>* found_node;
	TreeNode<T>* BuildTree(size_t h) {
		T input;
		TreeNode<T>* r00t = new TreeNode<T>;
		if (h == 0) {
			return nullptr;
		}
		cin >> input;
		r00t->value = input;
		r00t->left = BuildTree(h-1);
		r00t->right = BuildTree(h-1);
		return r00t;
	}
	TreeNode<T>* BuildRandomTree(size_t h) {
		T input;
		TreeNode<T>* r00t = new TreeNode<T>;
		if (h == 0) {
			return nullptr;
		}
		input = rand() % 11;
		r00t->value = input;
		r00t->left = BuildRandomTree(h - 1);
		r00t->right = BuildRandomTree(h - 1);
		return r00t;
	}
	void PrintTreeAsTree(TreeNode<T>* root, int level) {
		if (root) {
			PrintTreeAsTree(root->right, level + 1);
			for (int i = 0; i < level; i++) {
				cout << "   ";
			}
			cout << root->value << endl;
			PrintTreeAsTree(root->left, level + 1);
		}
	}
	void PrintTreeInOrder(TreeNode<T>* root) {
		if (root) {
			PrintTreeInOrder(root->left);
			cout << root->value << " ";
			PrintTreeInOrder(root->right);
		}
	}
	TreeNode<T>* SearchInsert(TreeNode<T>* r00t, T val) {
		if (r00t == nullptr) {
			TreeNode<T>* new_root = new TreeNode<T>;
			new_root->left = nullptr;
			new_root->right = nullptr;
			new_root->value = val;
			r00t = new_root;
			return r00t;
		}
		else {
			TreeNode<T>* prev = nullptr;
			TreeNode<T>* cur = r00t;
			bool found = false;
			while (cur && !found) {
				prev = cur;
				if (val == cur->value) {
					found = true;
				}
				else if (val < cur->value) {
					cur = cur->left;
				}
				else {
					cur = cur->right;
				}
			}
			if (found) {
				return cur;
			}
			TreeNode<T>* tnew = new TreeNode<T>;
			tnew->value = val;
			tnew->left = nullptr;
			tnew->right = nullptr;
			if (val < prev->value) {
				prev->left = tnew;
			}
			else {
				prev->right = tnew;
			}
			return tnew;
		}
	}
	TreeNode<T>* BuildRandomBST(int count) {
		T val;
		val = (rand() % 250) / 6;
		TreeNode<T>* r00t = SearchInsert(nullptr, val);
		for (int i = 1; i < count; i++) {
			val = (rand() % 250) / 6;
			SearchInsert(r00t, val);
		}
		return r00t;
	}
	TreeNode<T>* BuildBST(int count) {
		T val;
		cin >> val;
		TreeNode<T>* r00t = SearchInsert(nullptr, val);
		for (int i = 1; i < count; i++) {
			cin >> val;
			SearchInsert(r00t, val);
		}
		return r00t;
	}
	TreeNode<T>* DeleteByValue(T val, TreeNode<T>* rt) {
		if (rt) {
			if (rt->value == val) {
				rt = nullptr;
			}
			else {
				if ((rt->left) && (rt->left->value == val)) {
					rt->left = nullptr;
				}
				else if ((rt->right) && (rt->right->value == val)) {
					rt->right = nullptr;
				}
				else {
					DeleteByValue(val, rt->left);
					DeleteByValue(val, rt->right);
				}
			}
		}
		return rt;
	}
	TreeNode<T>* DeleteByAdress(TreeNode<T>* rt, TreeNode<T>* found_node) {
		if (rt) {
			if (rt == found_node) {
				rt = nullptr;
			}
			else {
				if (rt->left == found_node) {
					rt->left = nullptr;
				}
				else if (rt->right == found_node) {
					rt->right = nullptr;
				}
				else {
					DeleteByAdress(rt->left, found_node);
					DeleteByAdress(rt->right, found_node);
				}
			}
		}
		return rt;
	}
	bool Find(T val, TreeNode<T>* r00t) {
		TreeNode<T>* cur = r00t;
		bool found = false;
		if (cur) {
			if (cur->value == val) {
				found = true;
				found_node = cur;
				return true;
			}
			else {
				found = Find(val, cur->left);
				found = Find(val, cur->right);
			}
		}
		return false;
	}
};

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
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Input new full date" << endl;
		else  cout << "   Input new full date" << endl;
		if (key == 1) cout << "-> Calculate date difference" << endl;
		else  cout << "   Calculate date difference" << endl;
		if (key == 2) cout << "-> Day of the week" << endl;
		else  cout << "   Day of the week" << endl;
		if (key == 3) cout << "-> Print" << endl;
		else  cout << "   Print" << endl;
		if (key == 4) cout << "-> Back" << endl;
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
		if (key == 0) cout << "-> Take away from the current date" << endl;
		else  cout << "   Take away from the current date" << endl;
		if (key == 1) cout << "-> Add to the current date" << endl;
		else  cout << "   Add to the current date" << endl;
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

int main() {
	int enter;
	srand((unsigned)time(0));

	do {
		system("cls");
		enter = enter_menu();
		switch (enter) {
		case 0: {
			int demo_menu;
			do {
				system("cls");
				demo_menu = menu();
				switch (demo_menu) {
				case 0: {
					Full_Date dem = { Year(1944),Month(6),Day(6),Hour(6),Minute(30),Second(0) };
					Full_Date dem1 = { Year(2020),Month(10),Day(1),Hour(14),Minute(14),Second(14) };
					dem.Print();
					dem.DayOfTheWeek();
					dem1.Print();
					dem1.DayOfTheWeek();
					dem.DateDifference(dem1);
					cout << endl << "##Take away difference beetwen this dates from first date##" << endl << endl;
					dem.Arithmetic(0);
					dem.Print();
					dem = { Year(1944),Month(6),Day(6),Hour(6),Minute(30),Second(0) };
					dem1.DateDifference(dem);
					cout << endl << "##Add difference beetwen this dates to second date##" << endl << endl;
					dem1.Arithmetic(1);
					dem1.Print();
					system("pause");
					break;
				}
				case 1: {
					Matrix dem;
					cout << "#Set random matrix 15x15#" << endl;
					dem.GetRandomMatrix(15);
					dem.PrintMatrix();
					cout << endl << "#Get value in 7 row and 3 column#" << endl;
					dem.GetByIndex(7, 3);
					cout << endl << "#Get row and column of the first 0#" << endl;
					dem.GetByValue(0);
					cout << endl << "#Summation with random matrix#" << endl;
					dem.Sum();
					cout << endl << "#Multiplication by random matrix#" << endl;
					dem.MultiplicationByMatrix();
					cout << endl << "#Multiplication by random vector#" << endl;
					dem.MultiplicationByVector();
					cout << endl << "#Matrix transponation#" << endl;
					dem.Transponation();
					system("pause");
					break;
				}
				case 2: {
					cout << "###Int demo###" << endl;
					SparseList<int> dem;
					dem.GetRandomList(25);
					dem.PrintAll();
					cout << endl << "#Print value with index 13#" << endl;
					dem.GetValue(13);
					cout << endl << "#Print index for first 2#" << endl;
					dem.GetIndex(2);
					cout << endl << "#Search for first value: mod(value + index, 3) = 0 and value!=0 #" << endl;
					Node<int>* cur = dem.pbeg;
					bool is = false;
					while (cur) {
						if ((cur->index + cur->value) % 3 == 0) {
							is = true;
							cout << "[ " << cur->index << " ] " << cur->value << endl;
							break;
						}
						cur = cur->next;
					}
					if (!is) {
						cout << "No values to such condition" << endl;
					}
					cout << endl;
					dem.DeleteList();
					dem.Add(-8);
					dem.Add(0);
					dem.Add(0);
					dem.Add(8);
					dem.Add(3);
					dem.Add(0);
					dem.Add(0);
					dem.Add(0);
					dem.Add(0);
					dem.Add(2);
					dem.Add(0);
					dem.Add(14);
					dem.Add(12);
					dem.Add(9);
					dem.Add(0);
					dem.Add(0);
					dem.Add(0);
					dem.Add(0);
					dem.Add(1);
					dem.PrintAll();
					cout << endl << "#Search for first value: mod(value + index, 3) = 0 and value!=0 #" << endl;
					cur = dem.pbeg;
					is = false;
					while (cur) {
						if ((cur->index + cur->value) % 3 == 0) {
							is = true;
							cout << "[ " << cur->index << " ] " << cur->value << endl;
							break;
						}
						cur = cur->next;
					}
					if (!is) {
						cout << "No values to such condition" << endl;
					}
					cout << endl << endl << "###Double demo###" << endl;
					SparseList<double> dem1;
					dem1.DeleteList();
					dem1.Add(24.5);
					dem1.Add(-12.3);
					dem1.Add(4.01);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(-99.99);
					dem1.Add(0);
					dem1.Add(2.28);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(3.22);
					dem1.Add(9);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(0);
					dem1.Add(10.01);
					dem1.PrintAll();
					cout << endl << "#Print value with index 12#" << endl;
					dem1.GetValue(13);
					cout << endl << "#Print index for first 0#" << endl;
					dem1.GetIndex(0);
					system("pause");
					break;
				}
				case 3: {
					Tree<int> dem;
					cout << "Binary tree: " << endl;
					dem.root = dem.BuildRandomTree(5);
					cout << "\tTree form: " << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << "\tInOrder travestal form: " << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << endl << "#Find and delete by parent node last node with value 5#" << endl;
					dem.Find(5, dem.root);
					dem.root = dem.DeleteByAdress(dem.root,dem.found_node);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << endl << "#Delete all nodes with value 6#" << endl;
					dem.root = dem.DeleteByValue(6, dem.root);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << endl << "#Addition(BST-type) of 3, 5, 8, -4, 78 to the tree#";
					dem.SearchInsert(dem.root, 3);
					dem.SearchInsert(dem.root, 5);
					dem.SearchInsert(dem.root, 8);
					dem.SearchInsert(dem.root, -4);
					dem.SearchInsert(dem.root, 78);
					cout << "#Tree after all operations#" << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << endl << endl;
					cout << "BST: " << endl;
					dem.root = dem.BuildRandomBST(20);
					cout << "\tTree form: " << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					cout << "\tInOrder travestal form: " << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << endl << "#Delete node with value 33#" << endl;
					dem.root = dem.DeleteByValue(33, dem.root);
					dem.PrintTreeAsTree(dem.root, 0);
					cout << endl << "#Addition(BST-type) of 3, 5, 8, -4, 78 to the tree#";
					dem.SearchInsert(dem.root, 3);
					dem.SearchInsert(dem.root, 5);
					dem.SearchInsert(dem.root, 8);
					dem.SearchInsert(dem.root, -4);
					dem.SearchInsert(dem.root, 78);
					cout << "#Tree after all operations#" << endl;
					dem.PrintTreeInOrder(dem.root);
					cout << endl;
					dem.PrintTreeAsTree(dem.root, 0);
					system("pause");
					break;
				}
				}
			} while (demo_menu != 4);
			break;
		}
		case 1: {
			int theme;
			do {
				system("cls");
				theme = menu();
				switch (theme) {
				case 0: {
					int date;
					Full_Date test;
					test.Fill();
					do {
						system("cls");
						date = date_menu();
						switch (date) {
						case 0: {
							test.Fill();
							break;
						}
						case 1: {
							test.Print();
							Full_Date date_2;
							cout << "Input 2nd full date: " << endl;
							date_2.Fill();
							test.DateDifference(date_2);
							int dif = difference_menu();
							switch (dif) {
							case 0: {
								test.Arithmetic(0);
								break;
							}
							case 1: {
								test.Arithmetic(1);
								break;
							}
							}
							cout << "New date is: ";
							test.Print();
							system("pause");
							break;
						}
						case 2: {
							test.DayOfTheWeek();
							system("pause");
							break;
						}
						case 3: {
							test.Print();
							system("pause");
							break;
						}
						}
					} while (date != 4);
					break;
				}
				case 1: {
					int answer;
					Matrix matrix;
					matrix.GetRandomMatrix(10);
					do {
						system("cls");
						answer = matrix_menu();
						switch (answer) {
						case 0: {
							int n;
							cout << "Input matrix dimension: ";
							cin >> n;
							matrix.GetRandomMatrix(n);
							break;
						}
						case 1: {
							int n;
							cout << "Input matrix dimension: ";
							cin >> n;
							matrix.GetMatrix(n);
							break;
						}
						case 2: {
							matrix.PrintMatrix();
							system("pause");
							break;
						}
						case 3: {
							matrix.Sum();
							system("pause");
							break;
						}
						case 4: {
							matrix.MultiplicationByMatrix();
							system("pause");
							break;
						}
						case 5: {
							matrix.MultiplicationByVector();
							system("pause");
							break;
						}
						case 6: {
							matrix.Transponation();
							system("pause");
							break;
						}
						case 7: {
							int x, y;
							cout << "Input row and column to search value: ";
							cin >> x >> y;
							matrix.GetByIndex(x, y);
							system("pause");
							break;
						}
						case 8: {
							int n;
							cout << "Input value (0-4) to search indexes: ";
							cin >> n;
							matrix.GetByValue(n);
							system("pause");
							break;
						}
						}
					} while (answer != 9);
					break;
				}
				case 2: {
					int list;
					SparseList<int> sparse_list;
					sparse_list.GetRandomList(25);
					do {
						system("cls");
						list = list_menu();
						switch (list) {
						case 0: {
							int val;
							cout << "Input value to add: ";
							cin >> val;
							sparse_list.Add(val);
							break;
						}
						case 1: {
							int n;
							cout << "Input list lenth: ";
							cin >> n;
							sparse_list.GetList(n);
							break;
						}
						case 2: {
							int n;
							cout << "Input list lenth: ";
							cin >> n;
							sparse_list.GetRandomList(n);
							break;
						}
						case 3: {
							sparse_list.PrintAll();
							system("pause");
							break;
						}
						case 4: {
							size_t n;
							cout << "Input index to search: ";
							cin >> n;
							sparse_list.GetValue(n);
							system("pause");
							break;
						}
						case 5: {
							int n;
							cout << "Input value to search: ";
							cin >> n;
							sparse_list.GetIndex(n);
							system("pause");
							break;
						}
						}
					} while (list != 6);
					break;
				}
				case 3: {
					int tree;
					Tree<int> bin_tree;
					bin_tree.root = bin_tree.BuildRandomTree(5);
					do {
						system("cls");
						tree = binary_tree_menu();
						switch (tree) {
						case 0: {
							bin_tree.PrintTreeInOrder(bin_tree.root);
							system("pause");
							break;
						}
						case 1: {
							bin_tree.PrintTreeAsTree(bin_tree.root, 0);
							system("pause");
							break;
						}
						case 2: {
							size_t height;
							cout << "Input tree height: ";
							cin >> height;
							cout << "Input " << pow(2, height) - 1 << " values for this tree: ";
							bin_tree.root = bin_tree.BuildTree(height);
							break;
						}
						case 3: {
							size_t height;
							cout << "Input tree height: ";
							cin >> height;
							bin_tree.root = bin_tree.BuildRandomTree(height);
							break;
						}
						case 4: {
							size_t count;
							cout << "Input number of values: ";
							cin >> count;
							cout << "Input " << count << " values for this tree: ";
							bin_tree.root = bin_tree.BuildBST(count);
							break;
						}
						case 5: {
							size_t count;
							cout << "Input number of values: ";
							cin >> count;
							bin_tree.root = bin_tree.BuildRandomBST(count);
							break;
						}
						case 6: {
							int val;
							cout << "Input value to add: ";
							cin >> val;
							bin_tree.SearchInsert(bin_tree.root, val);
							break;
						}
						case 7: {
							int val;
							cout << "Input value to delete node: ";
							cin >> val;
							bin_tree.root = bin_tree.DeleteByValue(val, bin_tree.root);
							break;
						}
						case 8: {
							bin_tree.root = bin_tree.DeleteByAdress(bin_tree.root, bin_tree.found_node);	
							break;
						}
						case 9: {
							int val;
							cout << "Input value to search: ";
							cin >> val;
							bin_tree.found_node = nullptr;
							bin_tree.Find(val, bin_tree.root);
							if (bin_tree.found_node) {
								cout << "Adress of found node: " << bin_tree.found_node << endl;
							}
							else {
								cout << "Any node with such value don`t exist!" << endl;
							}
							system("pause");
							break;
						}
						}
					} while (tree != 10);
				}
				}
			} while (theme != 4);
			break;
		}
		}
	} while (enter != 2);

	return 0;
}