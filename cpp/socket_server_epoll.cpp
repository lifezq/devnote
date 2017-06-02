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
#include <fcntl.h>

#define SRV_PORT ((int)8888)
#define SRV_HELLO "Welcome to server! "
#define SRV_MAX_CONN ((int)1<<10) /* UnLimited */

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


    if(fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1){
        perror("Set non-block");
        exit(1);
    }

    printf("Listen on port:%d\n", port);

    int epfd = epoll_create(maxConn);

    struct epoll_event ep_event;
    struct epoll_event ep_events[maxConn+1];
    ep_event.events=EPOLLIN|EPOLLET;
    ep_event.data.fd=sockfd;

    if(epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ep_event)<0){
        perror("Epoll_ctl add error");
        exit(1);
    }

    int curfds=1, epfds, newsockfd;

    while(true){
   
        if((epfds=epoll_wait(epfd, ep_events, curfds, -1))<=0) continue;

        for(int i=0;i<epfds;i++){

            if(ep_events[i].data.fd==sockfd){
                if((newsockfd=accept(sockfd, (sockaddr*)&addr, (socklen_t*)&addr_len))<0){
                    perror("Newsock accept");
                    continue;
                }

                if(curfds>maxConn){
                    bzero(buf, sizeof(buf));
                    sprintf(buf, "Too many connections.\n");
                    send(newsockfd, buf, sizeof(buf), 0 );
                    shutdown(newsockfd, SHUT_RDWR);
                    continue;
                }
    
                ep_event.events=EPOLLIN|EPOLLET;
                ep_event.data.fd=newsockfd;
                
                if(epoll_ctl(epfd, EPOLL_CTL_ADD, newsockfd, &ep_event)<0){
                    perror("Epoll_ctl add error");
                    return -1;
                }
    
                curfds++;
    
                time_t timep;
                time(&timep);
                char srv_hello[50];
                bzero(srv_hello, sizeof(srv_hello));
                strcat(srv_hello, SRV_HELLO);
                strcat(srv_hello,  asctime(gmtime(&timep)));
                write(newsockfd, srv_hello, sizeof(srv_hello));
                
                printf("Connect from %s:%d\n", inet_ntoa(addr.sin_addr), addr.sin_port);
                continue;
            }

            

            bzero(buffer, sizeof(buffer));

            if(read(ep_events[i].data.fd, buffer, sizeof(buffer))<0 || strlen(buffer)==0){
                printf("Client[%d] Connection closed\n", ep_events[i].data.fd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, &ep_event);
                close(ep_events[i].data.fd);

                curfds--;

            }else{

                if(strlen(buffer) && buffer[0]!='\n') printf("Recved Client[%d]: %s", ep_events[i].data.fd, buffer);
                bzero(buf, sizeof(buf));
                if(strlen(buffer) && buffer[0]!='\n') sprintf(buf, "Client[%d] Message received.\n", ep_events[i].data.fd);
                if(send(ep_events[i].data.fd, buf, sizeof(buf), 0 )<0)  perror("S received.\n");
            }
        }
    }


    close(sockfd);

    return 0;
}
