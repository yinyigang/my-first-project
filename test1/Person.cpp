#include "Person.h"

string Person::getname() {
    return _name;
}

int Person::getage() {
    return _age;
}

void Person::setage(int age) {
    _age = age;
}

void Person:: setname(string name ) {
    _name = name;
}