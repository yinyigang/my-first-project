#pragma once    
#include <iostream>
#include <string>
#include "round.hpp"
#include <fstream>

using namespace std;

class Manager{
private:
    vector<Participant> participants;
    vector<Participant> participants1;
    vector<Participant> participants2;
    vector<Participant> participants3;
    char wait;
public:
    Manager() {
        participants.resize(12);
        participants1.resize(6);
        participants2.resize(6);
        participants3.resize(6);
    }
    static void showmenu() {
        cout << "---欢迎参加演讲比赛！---" << endl;
        cout << "-------请选择---------" << endl;
        cout << "----1 开始比赛--------" << endl;
        cout << "----2 查看往届记录-----" << endl;
        cout << "----3 删除往届记录-----" << endl;
        cout << "----4 退出-----------" << endl;
    }
    void startcompetition() {
        cout << "---选手正在报名---" <<endl;
        for (int i = 0; i<12; ++i) {
            char sub = 'A'+i;
            string name = (string) "Participant" + sub;
            participants[i] = Participant(name);
        }
        cout <<"---等待进入第一轮的比赛---" <<endl;
        cin >> wait;
        cout << "---第一轮比赛正式开始!---" <<endl;
        cout << "---第一组正在进行比赛---" << endl;
        for (int i = 0; i<6; ++i) {
            participants1[i] = participants[i];
        }
        round::setscore(participants1);
        printfirstthreescores(participants1);
        cout <<"---第二组正在进行比赛---" << endl;
        for (int i = 0; i<6; ++i) {
            participants2[i] = participants[i+6];
        }
        round::setscore(participants2);
        printfirstthreescores(participants2);
        for (int i = 0; i< 3; ++i) {
            participants3[2*i] = participants1[i];
            participants3[2*i+1] = participants2[i];
        }
        cout <<"---等待进入第二轮的比赛---" <<endl;
        cin >> wait;
        cout << "---第二轮比赛正式开始!---" <<endl;
        cout <<"---决赛组正在进行比赛---" << endl;
        round::setscore(participants3);
        printwinnerscores(participants3);
        writerecord();
    }
    static void printfirstthreescores(vector<Participant> &Participants) {
        cout << "前三名得分分别为" << endl;
        for (int i = 0; i<3; ++i) {
            cout << Participants[i].getname() << " : " << Participants[i].getfinalscore() << endl;
        }
    }
    static void printwinnerscores(vector<Participant> &Participants) {
        for (int i = 0; i<3; ++i) {
            cout << "第 " << i+1 << " 名: " << Participants[i].getname() << ", 得分： " << Participants[i].getfinalscore() << endl;
        }
    }
    void writerecord() {
        cout << "---正在记录比赛记录---" << endl;
        const char* filename = "./competitionrecords.txt";
        ofstream osm;
        osm.open(filename, ios::out|ios::binary);
        for (int i = 0; i<3; ++i) {
            Participant tem = participants3[i];
            osm.write(reinterpret_cast<char*>(&tem), sizeof(Participant));
        }
        osm.close();
    }
    static void showrecord() {
        const char* filename = "./competitionrecords.txt";
        ifstream ism;
        ism.open(filename, ios::in|ios::binary);
        cout << "上一次的比赛记录为：";
        Participant tem;
        while(!ism.eof()) {
            ism.read(reinterpret_cast<char*>(&tem), sizeof(Participant));
            cout << "参赛队员： " << tem.getname() << ",分数： " << tem.getfinalscore() << endl;
        }
        ism.close();
    }
};