#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SRV_PORT ((int)8888)
#define SRV_HELLO "Welcome to server! "
#define SRV_MAX_CONN ((int)1<<10) /* Limited by system max open files */

int main(int argc, char **argv){

    if(argc<=1){
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

    struct pollfd pfds[maxConn+1];

    pfds[0].fd=sockfd;
    pfds[0].events=POLLIN;

    for(int fd=1;fd<=maxConn;fd++) pfds[fd].fd=-1;

    int newsockfd, conn_full=-1;

    while(1){

        if(poll(pfds, (nfds_t)(maxConn+1), -1)<=0) continue;

        if(pfds[0].revents&POLLIN){
            if((newsockfd=accept(sockfd, (sockaddr*)&addr, (socklen_t*)&addr_len))<0){
                perror("Newsock accept");
                continue;
            }

            conn_full=1;
            for(int j=0;j<=maxConn;j++){
                if(pfds[j].fd==-1){
                    pfds[j].fd=newsockfd;
                    pfds[j].events=POLLIN;
                    conn_full=0;
                    break;
                }
            }

            if(conn_full){
                bzero(buf, sizeof(buf));
                sprintf(buf, "Too many connections.\n");
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
            
            printf("Connect from %s:%d\n", inet_ntoa(addr.sin_addr), addr.sin_port);
        }

        for(int i=1;i<=maxConn;i++){

            if(pfds[i].fd==-1) continue;
            if((pfds[i].revents&POLLIN)==POLLIN){

                bzero(buffer, sizeof(buffer));

                if(read(pfds[i].fd, buffer, sizeof(buffer))<0 || strlen(buffer)==0){
                    printf("Client[%d] Connection closed\n", i);
                    close(pfds[i].fd);
                    pfds[i].fd=-1;
                    pfds[i].events=0;
                }else{

                    if(strlen(buffer) && buffer[0]!='\n') printf("Recved Client[%d]: %s", i, buffer);
                    bzero(buf, sizeof(buf));
                    if(strlen(buffer) && buffer[0]!='\n') sprintf(buf, "Client[%d] Message received.\n", i);
                    if(send(pfds[i].fd, buf, sizeof(buf), 0 )<0)  perror("S received.\n");
                }
            }
        }
    }

    return 0;
}
