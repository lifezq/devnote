#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SRV_HOST "127.0.0.1"
#define SRV_PORT ((int)8888)

int main(int argc, char **argv){

    if(argc==1){
        printf("Cmd [host(default:%s)] [port(default:%d)]\n\n", SRV_HOST, SRV_PORT);
    }

    const char *host=(argc>=2)?argv[1]:SRV_HOST;
    int port=(argc>=3)?atoi(argv[2]):SRV_PORT;

    struct sockaddr_in addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        perror("Socket");
        exit(1);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    inet_aton(host, &addr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))){
        perror("Connect");
        exit(1);
    }


    char buffer[256];
    bzero(buffer, sizeof(buffer));
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("%s", buffer);
    while(1){

        bzero(buffer, sizeof(buffer));
        if(read(STDIN_FILENO, buffer, sizeof(buffer))<0 || strlen(buffer)==0){
            printf("Connection close..");
            close(sockfd);
            exit(0);
        }else{

            if(send(sockfd, buffer, sizeof(buffer), 0)<0){
                perror("Send");
                exit(1);
            }

            bzero(buffer, sizeof(buffer));
            recv(sockfd, buffer, sizeof(buffer), 0);
            printf("%s", buffer);
        }
    }

    return 0;
}
