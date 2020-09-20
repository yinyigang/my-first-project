#include <iostream>
#include <cstdlib>
#include <string> 
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

#define SER_PORT 9527

void sys_err(const char* str) {
    perror(str);
    exit(1);
}

int main(int argc, char* argv[]) {
    int cfd;
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1) sys_err("socket error");
    sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SER_PORT);
    inet_pton(AF_INET, "10.0.2.15", &ser_addr.sin_addr.s_addr);
    int ret = 0;
    ret = connect(cfd, (sockaddr*)&ser_addr, sizeof(ser_addr));
    if (ret != 0) sys_err("connect error");
    while(1) {
        char buf[1024];
        cin.getline(buf, 1024);
        write(cfd, buf, strlen(buf));
        ret = read(cfd, buf, strlen(buf));
        for (int i = 0; i<ret; ++i) {
            if (i == ret-1) cout << buf[i] << endl;
            else cout << buf[i];
        }
    }
    close(cfd);
    return 0;
}