#include <string>
#include <vector>
#include <iostream>

using namespace std;

//алгоритм КМП
int KMP(const string& S, int begin, const string& pattern) {
	vector<int> pf(pattern.length());
	pf[0] = 0;
	for (int k = 0, i = 1; i < pattern.length(); ++i) {
		while ((k > 0) && (pattern[i] != pattern[k])) {
			k = pf[k - 1];
		}
		if (pattern[i] == pattern[k]) {
			k++;
		}
		pf[i] = k;
	}
	for (int k = 0, i = begin; i < S.length(); ++i) {
		while ((k > 0) && (pattern[k] != S[i])) {
			k = pf[k - 1];
		}
		if (pattern[k] == S[i]) {
			k++;
		}
		if (k == pattern.length()) {
			return (i - pattern.length() + 1);
		}
	}
	return -1;
}

//алгоритм Рабіна-Карпа
int RK_search(const string& str, const string& substr) {
	const int p = 31;
	std::vector<long long> p_pow(max(str.length(), substr.length()));
	p_pow[0] = 1;
	for (size_t i = 1; i < p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;
	std::vector<long long> h(str.length());
	for (size_t i = 0; i < str.length(); ++i) {
		h[i] = (str[i] - 'a' + 1) * p_pow[i];
		if (i)  h[i] += h[i - 1];
	}
	long long h_s = 0;
	for (size_t i = 0; i < substr.length(); ++i) {
		h_s += (substr[i] - 'a' + 1) * p_pow[i];
	}
	for (size_t i = 0; i + substr.length() - 1 < str.length(); ++i) {
		long long cur_h = h[i + substr.length() - 1];
		if (i)  cur_h -= h[i - 1];
		if (cur_h == h_s * p_pow[i])
			return i;
	}
	return -1;
}

//наївний алгоритм
int native(const string& s, const string& c, int n) {
	int i, j;
	int lenC = c.size();
	int lenS = s.size();
	for (i = 0; i <= lenS - lenC; i++) {
		for (j = 0; s[i + j] == c[j]; j++);
		if ((j - lenC == 1) && (i == lenS - lenC) && !(n - 1)) {
			return i;
		}
		if (j == lenC) {
			if (n - 1) {
				n--;
			}
			else {
				return i;
			}
		}
	}
	return -1;
}

//алгоритм Хорспула
int HorspoolMatch(const string& T, const string& P) {
	int n = T.size();
	int m = P.size();
	int Slide[255];
	for (int i = 0; i < 255; i++){
		Slide[i] = m;
	}
	for (int l = 0; l < m - 1; l++) {
		Slide[P[l]] = m - 1 - l;
	}
	int i = m - 1;
	while (i <= (n - 1)) {
		int k = 0;
		while (k <= m - 1 && P[m - 1 - k] == T[i - k]) {
			k = k + 1;
		}
		if (k == m) {
			return i - m + 1;
		}
		else {
			i = i + Slide[T[i]];
		}
	}
	return -1;
}

//алгоритм Боєра-Мура
int BMSearch(const string& str, const string& substr) {
	int  sl = str.size();
	int ssl = substr.size();
	int  i, Pos;
	int  BMT[256];
	for (i = 0; i < 256; i++)
		BMT[i] = ssl;
	for (i = ssl - 1; i >= 0; i--)
		if (BMT[substr[i]] == ssl)
			BMT[substr[i]] = ssl - i - 1;
	Pos = ssl - 1;
	while (Pos < sl) {
		if (substr[ssl - 1] != str[Pos]) {
			Pos = Pos + BMT[str[Pos]];
		}
		else {
			for (i = ssl - 2; i >= 0; i--) {
				if (substr[i] != str[Pos - ssl + i + 1]) {
					Pos += BMT[(short)(str[Pos - ssl + i + 1])] - 1;
					break;
				}
				else {
					if (i == 0) {
						return Pos - ssl + 1;
					}
				}
			}
		}
	}
	return -1;
}

int main() {
	return 0;
}