#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SRV_PORT ((int)8888)
#define SRV_HELLO "Welcome to server! "
#define SRV_MAX_CONN ((int)2)

int main(int argc, char **argv){

    if(argc<=1){
        printf("Usage:\n");
        printf("Cmd [port(default:8888)] [max conn(default:2)]\n\n");
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

    if(bind(sockfd, (const sockaddr*)&addr, sizeof(struct sockaddr_in))){
        perror("bind");
        exit(1);
    }

    if(listen(sockfd, maxConn)){
        perror("listen");
        exit(1);
    }

    printf("Listen on port:%d\n", port);

    fd_set readfds;
    maxConn=maxConn+sockfd;
    int is_connected[maxConn+1],  newsockfd;
    for(int fd=sockfd;fd<=maxConn;fd++) is_connected[fd]=0;

    while(1){

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        for(int fd=sockfd;fd<=maxConn;fd++) if(is_connected[fd]) FD_SET(fd, &readfds);
        if(!select (maxConn+1, &readfds, NULL, NULL, NULL)) continue;

        for(int fd=sockfd;fd<=maxConn;fd++){

            if(FD_ISSET(fd, &readfds)){

                if(sockfd == fd){
                    if((newsockfd=accept(sockfd, (sockaddr*)&addr, (socklen_t*)&addr_len))<0){
                        perror("newsock accept");
                        continue;
                    }

                    if(newsockfd > maxConn){
                        bzero(buf, sizeof(buf));
                        sprintf(buf, "Too many connections.\n", newsockfd);
                        send(newsockfd, buf, sizeof(buf), 0 );
                        shutdown(newsockfd, SHUT_RDWR);
                        continue;
                    }

                    time_t timep;
                    time(&timep);
                    char srv_hello[50];
                    bzero(srv_hello, sizeof(srv_hello));
                    strcat(srv_hello, SRV_HELLO);
                    strcat(srv_hello,  asctime(gmtime(&timep)));
                    write(newsockfd, srv_hello, sizeof(srv_hello));

                    is_connected[newsockfd]=1;
                    
                    printf("Connect from %s\n", inet_ntoa(addr.sin_addr));
                }else{


                    bzero(buffer, sizeof(buffer));
                    if(read(fd, buffer, sizeof(buffer))<0 || strlen(buffer)==0){
                        printf("Client[%d] Connection closed\n", fd);
                        is_connected[fd]=0;
                        close(fd);
                    }else{


                        if(strlen(buffer) && buffer[0]!='\n') printf("Recved Client[%d]: %s", fd, buffer);

                        bzero(buf, sizeof(buf));
                        if(strlen(buffer) && buffer[0]!='\n') sprintf(buf, "Client[%d] Message received.\n", fd);

                        if(send(fd, buf, sizeof(buf), 0 )<0)  perror("S received.\n");
                    }
                }
            }
        }
    }

    return 0;
}
