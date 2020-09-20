#include <iostream>
#include <cstdlib>
#include <string> 
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define SER_PORT 9527
#define BURSIZ 1024

void sys_err(const char* str) {
    perror(str);
    exit(1);
}

int main(int argc, char* argv[]){
    int lfd = 0;
    sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SER_PORT);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) sys_err("socket error");
    int tem;
    tem = bind (lfd, (sockaddr*)&ser_addr, sizeof(ser_addr));
    if (tem == -1) sys_err("bind error");
    listen(lfd, 128);
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr_len);
    int cfd;
    cfd = accept(lfd, (sockaddr*)&client_addr, &client_addr_len);
    if (cfd == -1) sys_err("accept error");
    char client_IP[BURSIZ];
    printf("client ip: %s port: %d\n",
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_IP, sizeof(client_IP)),
        ntohs(client_addr.sin_port));
    int ret;
    char buf[BURSIZ];
    char buf1[BUFSIZ];
    while(1) {
        ret = read(cfd, buf, sizeof(buf));
        if (ret == 0) break;
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
    close(lfd);
    close(cfd);
    return 0;
}
