#pragma once
#include <iostream>

using namespace std;

int S = 0;

class Base {
private:
    int n;
public:
    Base() {
        this->n = ++number;
    }
    int cur_num() {
        return this->n;
    }
    virtual ~Base();
    static int number;
};
int Base::number = 0;

Base::~Base() {
    S = 2 * S - this->n + 11;
    cout << "Base was destroyed" << endl << "Now S is: " << S << endl;
}

class Alpha : public Base {
public:
    ~Alpha() {
        S = S - 2 * cur_num() + 11;
        cout << "Alpha was destroyed" << endl << "Now S is: " << S << endl;
    }
};

class Beta : public Base {
public:
    ~Beta() {
        S = S - cur_num();
        cout << "Beta was destroyed" << endl << "Now S is: " << S << endl;
    }
};


class Gamma : public Base {
public:
    ~Gamma() {
        S = S + 3 * cur_num();
        cout << "Gamma was destroyed" << endl << "Now S is: " << S << endl;
    }
};