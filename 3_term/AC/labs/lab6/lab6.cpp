#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    return pi;
}

bool isCyclicOffset(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) return false;
    if (str1.empty() && str2.empty()) return true;
    string tmp = str1 + "#" + str2 + str2;
    vector<int> z = prefix_function(tmp);
    for (int num : z) {
        if (num == str2.size()) {
            return true;
        }
    }
    return false;
}

int main() {
    return 0;
}