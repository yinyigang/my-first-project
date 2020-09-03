#include "Participant.hpp"
#include "round.hpp"
#include "Manager.hpp"

int main() {
    while (true) {
        Manager m;
        Manager::showmenu();
        char choice;
        cin >> choice; 
        switch(choice) {
            case '1':
                m.startcompetition();
                break;
            case '2':
                Manager::showrecord();
                break;
            case '4':
                cout << "---正在退出演讲比赛---" << endl;
                return 0;
            default:
                cout << "请输入有效数字！" << endl;
        }
    }
    return 0;
}