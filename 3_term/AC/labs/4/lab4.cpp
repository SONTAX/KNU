#include <iostream>
#include <vector>

using namespace std;

void sort1(vector <pair <int, char>>& a) {
    vector <pair <int, char>> result;
    int p = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].first == 0)
            result.push_back(a[i]);
    }
    for (int i = 0; i < a.size; i++) {
        if (a[i].first == 1)
            result.push_back(a[i]);
    }
    a = result;
}


void sort2(vector <pair <int, char>>& a) {
    int p = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].first == 0) {
            swap(a[p], a[i]);
            p++;
        }
    }
}


void sort3(vector <pair <int, char>>& a) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int j = 0; j < a.size() - 1; j++) {
            if (a[j].first > a[j + 1].first) {
                swap(a[j], a[j + 1]);
                flag = true;
            }
        }
    }
}

int main()
{
    return 0;
}