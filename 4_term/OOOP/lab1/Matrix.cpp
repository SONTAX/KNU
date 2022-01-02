#include "Matrix.h"

string Matrix::PrintMatrix() const {
	string output;
	int k = 0;
	int size = col.size();
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (k < size) {
				if ((row[k] == i) && (col[k] == j)) output += to_string(val[k++]) + " ";
				else output += "0 ";
			}
			else output += "0 ";
		}
		output += "\n";
	}
	return output;
}

void Matrix::GetMatrix(int n) {
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

void Matrix::GetRandomMatrix(int n) {
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

void Matrix::GetByIndex(int rw, int cl) {
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

void Matrix::GetByValue(int value) {
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

void Matrix::Sum() {
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
	cout << PrintMatrix();
	cout << "MATRIX B" << endl;
	cout << B.PrintMatrix();
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

void Matrix::MultiplicationByMatrix() {
	Matrix A;
	A.val = val;
	A.col = col;
	A.row = row;
	Matrix B;
	B.GetRandomMatrix(dimension);
	cout << "MATRIX A" << endl;
	cout << PrintMatrix();
	cout << "MATRIX B" << endl;
	cout << B.PrintMatrix();
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

void Matrix::MultiplicationByVector() {
	int ka = 0;
	int size_a = col.size();
	int** a = new int* [dimension];
	cout << "MATRIX A" << endl;
	cout << PrintMatrix();
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
		cout << b[i] << endl;
	}
	cout << endl << "RESULT" << endl;
	for (size_t i = 0; i < dimension; i++) {
		for (size_t j = 0; j < dimension; j++) {
			c[i] += a[i][j] * b[j];
		}
		cout << c[i] << endl;
	}
	cout << endl;
	for (size_t i = 0; i < dimension; i++) {
		delete[] a[i];
	}
	delete[] a;
}

void Matrix::Transponation() {
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