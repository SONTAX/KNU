#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

//функція, яка перевіряє чи є у файлі більше 1 елементу, тобто чи потрібно розбивати файл на менші
bool check_file(const string& file_name) {
	string file_to_check = file_name + ".txt";
	ifstream f(file_to_check);
	int tmp;
	int flag = 0;
	while (f >> tmp) flag++;
	if (flag > 1) {
		f.close();
		return true;
	}
	f.close();
	return false;
}

//функція розподілу файла на два менших
void split_file_in_two(const string& sourse, const string& filename1, const string& filename2) {
	ifstream f(sourse + ".txt");
	ofstream f1(filename1 + ".txt");
	ofstream f2(filename2 + ".txt");
	int tmp;
	int i = 0;
	while (f >> tmp) {
		if (i % 2 == 0) f1 << tmp << " ";
		else f2 << tmp << " ";
		i++;
	}
	f.close();
	f1.close();
	f2.close();
}

//функція злиття файлів file1, file2 у файл source
void merge(const string& sourse, const string& filename1, const string& filename2) {
	ofstream f(sourse + ".txt");
	ifstream f1(filename1 + ".txt");
	ifstream f2(filename2 + ".txt");
	int tmp1, tmp2;
	bool used1 = true;
	bool used2 = true;
	bool flag1 = false;
	bool flag2 = false;
	while (!flag1 || !flag2) {
		if (used1 == true) {
			if (f1 >> tmp1) {
				used1 = false;
			}
			else {
				flag1 = true;
			}
		}
		if (used2 == true) {
			if (f2 >> tmp2) {
				used2 = false;
			}
			else {
				flag2 = true;
			}
		}

		if (used1 && !used2) {
			f << tmp2 << " ";
			used2 = true;
		}
		else if (used2 && !used1) {
			f << tmp1 << " ";
			used1 = true;
		}
		else if (!used1 && !used2) {
			if (tmp1 > tmp2) {
				f << tmp2 << " ";
				used2 = true;
			}
			else {
				f << tmp1 << " ";
				used1 = true;
			}
		}
	}
	f.close();
	f1.close();
	f2.close();
	const string delete1 = filename1 + ".txt";
	const string delete2 = filename2 + ".txt";
	remove(delete1.c_str());
	remove(delete2.c_str());
}

//рекурсівна функція, що сортує файл file_name
void merge_sort(const string& file_name) {
	if (check_file(file_name)) {
		const string shared_file_1 = file_name + "1";
		const string shared_file_2 = file_name + "2";
		split_file_in_two(file_name, shared_file_1, shared_file_2);
		merge_sort(shared_file_1);
		merge_sort(shared_file_2);
		merge(file_name, shared_file_1, shared_file_2);
	}
}

int main() {
	merge_sort("sort.txt");
	return 0;
}