#pragma once
#include <type_traits>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

long long factorial(long number) {
	if (number <= 1)
		return 1;
	else
		return number * factorial(number - 1);
}

long long pw(long a, long b) {
	long long res = 1;
	while (b > 0) {
		res *= a;
		b--;
	}
	return res;
}

struct Node {
	int value;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class List {
private:
	Node* pbeg = nullptr;
	Node* pend = nullptr;
public:
	Node* begin() {
		return pbeg;
	}
	void add(int val) {
		Node* new_node = new Node;
		new_node->value = val;
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
	void clear() {
		Node* cur = pbeg;
		while (cur) {
			Node* to_delete = cur;
			cur = cur->next;
			delete to_delete;
		}
		pbeg = nullptr;
		pend = nullptr;
	}
	void print() {
		Node* current = pbeg;
		while (current != nullptr) {
			std::cout << current->value << " ";
			current = current->next;
		}
	}
	template<typename T, typename Q>
	void func(std::pair<T, Q> s) {
		this->clear();
		List first;
		List second;
		first.func(s.first);
		second.func(s.second);
		Node* fir = first.begin();
		Node* sec = second.begin();
		while (sec) {
			fir = first.begin();
			while (fir) {
				if (sec->value == fir->value) {
					this->add(sec->value);
				}
				fir = fir->next;
			}
			sec = sec->next;
		}

	}
	template<typename T>
	void func(T t) {
		this->clear();
		if constexpr (std::is_integral<T>::value) {
			if (t > 0) {
				long long temp;
				for (int k = 2; k <= 111; k++) {
					temp = (factorial(t) - (t * t)) % k;
					this->add(temp);
				}
			}
			else if (t < 0) {
				long long temp = (pw(t, 8) + pw(t, 3)) % 211;
				std::vector<int> r;
				do {
					r.push_back(temp % 4);
					temp = temp / 4;
				} while (temp > 0);
				for (int i = r.size() - 1; i >= 0; i--) {
					this->add(r[i]);
				}
			}

		}
		else if constexpr (std::is_floating_point<T>::value) {
			for (int k = 1; k <= 42; k++) {
				long double temp = (long long)(expl(1 / cosl(k * t))) % 311;
				this->add(temp);
			}
		}
		else {
			this->add(4);
			this->add(0);
			this->add(71);
		}
	}
	void func(string t) {
		this->clear();
		string temp;
		for (size_t i = 1; i < t.size(); i++) {
			if (i > 1) {
				if ((t[i - 1] >= '0') && (t[i - 1] <= '9') && (t[i] >= '0') && (t[i] <= '9') && ((t[i + 1] > '9') || (t[i + 1] < '0')) && ((t[i - 2] > '9') || (t[i - 2] < '0'))) {
					temp = t[i - 1];
					temp += t[i];
					long long k = stoi(temp);
					k = pw(k, k);
					this->add(k % 411);
				}
			}
			else if (i == 1) {
				if ((t[i - 1] >= '0') && (t[i - 1] <= '9') && (t[i] >= '0') && (t[i] <= '9') && ((t[i + 1] > '9') || (t[i + 1] < '0'))) {
					temp = t[i - 1];
					temp += t[i];
					long long k = stoi(temp);
					k = pw(k, k);
					this->add(k % 411);
				}
			}
			else if (i == (t.size() - 1)) {
				if ((t[i - 1] >= '0') && (t[i - 1] <= '9') && (t[i] >= '0') && (t[i] <= '9') && ((t[i - 2] > '9') || (t[i - 2] < '0'))) {
					temp = t[i - 1];
					temp += t[i];
					long long k = stoi(temp);
					k = pw(k, k);
					this->add(k % 411);
				}
			}
		}
	}
};