#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Participant {
private:
    string name;
    vector<int> scores;
    int finalscore;
public:
    Participant() {
        scores.resize(10, 0);
    }
    ~Participant() {

    }
    // void operator()(const Participant &p) {
    //     this->name = p.getname();
    //     this->finalscore = p.getfinalscore();
    // }
    // void operator=(const Participant &p) {
    //     this->name = p.getname();
    //     this -> finalscore = p.getfinalscore();
    // }
    Participant(string name) {
        this->name = name;
    }
    void setscore(int n, int score) {
        scores[n] = score;
    }
    string getname() const {
        return name;
    }
    void calfinalscore() {
        int maxs = 0;
        int mins = 100;
        int totalscore = 0;
        for (vector<int>::iterator it = scores.begin(); it!= scores.end(); ++it) {
            if  (*it>maxs) maxs = *it;
            if (*it < mins) mins = *it;
            totalscore += *it;
        }
        finalscore = (totalscore - maxs - mins)/8;
    }
    int getfinalscore() const {
        return finalscore;
    }
};