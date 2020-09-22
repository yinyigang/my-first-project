#include <iostream>
#include <cstdlib>
#include <string> 
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <strings.h>

using namespace std;

#define SER_PORT 9527

void sys_err(const char* str) {
    perror(str);
    exit(1);
}

void childwork(int cfd, sockaddr_in* client_addr) {
    char buf[BUFSIZ];
    char buf1[BUFSIZ];
    while(1) {
        int ret = read(cfd, buf, sizeof(buf));
        if (ret == 0) {
            break;
        }
        char client_IP[BUFSIZ];
        printf("client ip: %s port: %d\n",
            inet_ntop(AF_INET, &(client_addr->sin_addr.s_addr), client_IP, sizeof(client_IP)),
            ntohs(client_addr->sin_port));
        for (int i = 0; i<ret; ++i) {
            if (i == ret-1) {
                cout << buf[i] << endl;
                buf1[i] = buf[i];
            }
            else {
                cout << buf[i];
                buf1[i] = buf[i];
            }
        }
        write(cfd, buf1, ret);
    }
    close(cfd);
    return;
} 

int main(int argc, char* argv[]){
    int lfd = 0;
    sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SER_PORT);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) sys_err("socket error");
    int opt;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));
    int ret;
    ret = bind (lfd, (sockaddr*)&ser_addr, sizeof(ser_addr));
    if (ret == -1) sys_err("bind error");
    listen(lfd, 128);
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr_len);
    int cfd;
    int pid;
    int pnum = 0;
    thread threadpool[256];
    while(1) {
        if ((cfd = accept(lfd, (sockaddr*)&client_addr, &client_addr_len)) <0) {
            if (errno == EINTR) continue;
            else sys_err("accept error");
        }
        threadpool[pnum] = thread (childwork, cfd, &client_addr);
        threadpool[pnum].detach();
        pnum++;
    }
    return 0;
}
