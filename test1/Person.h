#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
    private:
    int _age;
    string _name;
    public:
string getname() {
    return _name;
}

int getage() {
    return _age;
}

void setage(int age) {
    _age = age;
}

void setname(string name ) {
    _name = name;
}
};
