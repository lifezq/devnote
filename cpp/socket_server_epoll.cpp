#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SRV_PORT ((int)8888)
#define SRV_HELLO "Welcome to server! "
#define SRV_MAX_CONN ((int)1<<10) /* Limited by system max open files */

int main(int argc, char **argv){

    if(argc==1){
        printf("Usage:\n");
        printf("Cmd [port(default:%d)] [max conn(default:%d)]\n\n", SRV_PORT, SRV_MAX_CONN);
    }

    int port=argc>=2?atoi(argv[1]):SRV_PORT;
    int maxConn=argc>=3?atoi(argv[2]):SRV_MAX_CONN;

    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[256], buf[30];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        perror("Socket error:");
        exit(1);
    }

    printf("Created sockfd:%d\n", sockfd);

    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);

    int opt=1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0){
        perror("setsockopt");
    }

    if(bind(sockfd, (const sockaddr*)&addr, sizeof(struct sockaddr_in))){
        perror("bind");
        exit(1);
    }

    if(listen(sockfd, 1<<9)){
        perror("listen");
        exit(1);
    }

    printf("Listen on port:%d\n", port);


    return 0;
}
