/*************************************************************************
    > File Name: updcli.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月13日 星期四 15时27分23秒
 ************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../comm/mybase.h"

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen) {

    fd_set rset;
    int maxfdid, n;
    char recv[MAXLINE];
    memset(&recv, 0, sizeof(recv));
    maxfdid = max(fileno(fp), sockfd) + 1;
    while(1) {
        FD_ZERO(&rset);
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        if (select(maxfdid, &rset, NULL, NULL, NULL) < 0) {
            if (errno == EINTR)
                break;
            else
                err_exit("select error!");
        }
        if (FD_ISSET(fileno(fp), &rset)) {
            if ((n = read(fileno(fp), &recv, MAXLINE)) > 0){
                if ((n = sendto(sockfd, &recv, strlen(recv), 0, pservaddr, servlen)) < 0)
                    err_exit("sendto error!");
                memset(&recv, 0, sizeof(recv));
            } else
                err_exit("read error!");
        }
        if (FD_ISSET(sockfd, &rset)) {
            if ((n = recvfrom(sockfd, &recv, MAXLINE, 0, NULL, NULL)) > 0) {
                recv[n] = '\n';
                if ((n = write(fileno(fp), &recv, n + 1)) < 0)
                    err_exit("write error");
                memset(&recv, 0, sizeof(recv));
            } else
                err_exit("recvfrom error!");
        }
    }
}

int main (int argc, char **argv) {

    if (argc < 3) {
        printf("invalid address!\n");
        exit(-1);
    }
    int sockfd, bro;
    char *opt = argv[3];
    if (argc > 3 && strcmp(opt, "-b") == 0) {
        bro = 1;
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (bro == 1) {
        printf("use broadcast!\n");
        setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &bro, sizeof(bro));
    }
    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        err_exit("connect error!");
    }
    printf("Address:%s\n", argv[1]);
    printf("Port:%s\n", argv[2]);
    dg_cli(stdin, sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
}
