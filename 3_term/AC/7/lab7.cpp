﻿//алгоритм Рабіна-Карпа
int RK_search(const std::string& str, const std::string& substr) {
	const int p = 31;
	std::vector<long long> p_pow(max(str.length(), subsrt.length()));
	p_pow[0] = 1;
	for (size_t i = 1; i < p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;

	std::vector<long long> h(str.length());
	for (size_t i = 0; i < str.length(); ++i)
	{
		h[i] = (str[i] - 'a' + 1) * p_pow[i];
		if (i)  h[i] += h[i - 1];
	}

	long long h_s = 0;
	for (size_t i = 0; i < substr.length(); ++i)
		h_s += (substr[i] - 'a' + 1) * p_pow[i];

	for (size_t i = 0; i + substr.length() - 1 < str.length(); ++i)
	{
		long long cur_h = h[i + substr.length() - 1];
		if (i)  cur_h -= h[i - 1];
		if (cur_h == h_s * p_pow[i])
			return i;
	}

	return -1;
}

//узагальнення алгоритму Рабіна-Карпа
std::pair<int, int> RK_matrix(const std::vector<std::string>& text, const std::vector<str::string>& pattern) {
	int m = text.size();
	int n = pattern.size();

	for (int row = 0; i < m - n + 1; row++) {

		int firstEntryCol = -1;
		int prevCol = -1;

		do {
			prevCol = firstEntryCol;
			firstEntryCol = RK_search(text[row].substr(prevCol + 1, n), pattern[0]);

			if (firstEntryCol >= 0) {

				firstEntryCol += prevCol;

				bool entry = true;

				for (int j = 0; j < n; j++) {
					if (RK_search(text[row + j].substr(firstEntryCol, n), pattern[j]) != 0) {
						entry = false;
						break;
					}
				}

				if (entry)
					return { row, firstEntryCol };
			}

		} while (firstEntryCol != -1);

	}

	return { -1, -1 };

}