#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
    private:
    int _age;
    string _name;
    public:
    void setage(int age);
    void setname(string name );
    int getage();
    string getname();
};
