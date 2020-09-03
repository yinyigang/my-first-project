#pragma once
#include "Participant.hpp"
#include <cstdlib>
#include <algorithm>

class round {
private:
    static bool comapreParticipant(Participant p1, Participant p2) {
        return p1.getfinalscore() > p2.getfinalscore();
    }
public:
    static void setscore(vector<Participant> &Participants) {
        for (vector<Participant>::iterator it = Participants.begin(); it != Participants.end(); ++it) {
            cout << "--- " << it->getname() << " 选手正在进行比赛---" << endl;
            for (int i = 0; i<10; ++i) {
                int score = rand()%40+60;
                it->setscore(i, score);
            }
            it->calfinalscore();
            cout <<  it->getname() << " 选手的平均分为: " <<it->getfinalscore()<<endl;
        }
        sortscores(Participants);
    }
    static void sortscores(vector<Participant> &Participants) {
        sort(Participants.begin(), Participants.end(), comapreParticipant);
    }
};