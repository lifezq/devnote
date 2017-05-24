#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SRV_PORT 8888
#define SERVER_HELLO "Welcome to server! "

int main(){

    struct sockaddr_in addr;
    int addr_len = sizeof(struct sockaddr_in);
    char buffer[256];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        perror("socket error:");
        exit(1);
    }

    printf("Created sockfd:%d\n", sockfd);

    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port = htons(SRV_PORT);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sockfd, (const sockaddr*)&addr, sizeof(addr))){
        perror("bind");
        exit(1);
    }

    if(listen(sockfd, 5)){
        perror("listen");
        exit(1);
    }

    printf("Listen on port:%d\n", SRV_PORT);

    fd_set readfds;
    int is_connected[10],  newsockfd;
    for(int fd=0;fd<10;fd++) is_connected[fd]=0;

    while(1){

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        for(int fd=0;fd<10;fd++) if(is_connected[fd]) FD_SET(fd, &readfds);
        if(!select (10, &readfds, NULL, NULL, NULL)) continue;


        for(int fd=0;fd<10;fd++){

            if(FD_ISSET(fd, &readfds)){

                if(sockfd == fd){
                    if((newsockfd=accept(sockfd, (sockaddr*)&addr, (socklen_t*)&addr_len))<0){
                        perror("newsock accept");
                        continue;
                    }

                    // write(newsockfd, SERVER_HELLO, sizeof(SERVER_HELLO));
                    time_t timep;
                    time(&timep);
                    char t[50];
                    bzero(t, sizeof(t));
                    strcat(t, SERVER_HELLO);
                    strcat(t,  asctime(gmtime(&timep)));
                    write(newsockfd, t, strlen(t));

                    is_connected[newsockfd]=1;
                    
                    printf("Connect from %s\n", inet_ntoa(addr.sin_addr));
                }else{


                    bzero(buffer, sizeof(buffer));
                    if(read(fd, buffer, sizeof(buffer))<0 || strlen(buffer)==0){
                        printf("Connect closed\n");
                        is_connected[fd]=0;
                        close(fd);
                    }else{

                        char buf[30];
                        sprintf(buf, "Client[%d] Message received.\n", fd);
                        if(send(fd, buf, sizeof(buf), 0 )<0){
                            perror("S received.\n");
                        }
                    }
                }
            }
        }
    }

    return 0;
}
