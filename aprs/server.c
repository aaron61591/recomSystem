/*************************************************************************
    > File Name: server.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时27分58秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "comm/netcommon.h"
#include "comm/mybase.h"
#include "comm/daemon.h"

char fpath[50] = {0};
char pidfile[50] = {0};

void handle(char *msg, struct sockaddr_in *cliaddr) {

    char tmp[4];
    sprintf(tmp, "%d", getpid());
    fin_exit(tmp);
}

void run_check() {

    if (file_exist(pidfile) == 0)
        err_exit("aprs is already running now!");
}

void run_lock() {

    FILE *fp;
    int pid = getpid();
    char pstr[5];
    sprintf(pstr, "%d", pid);
    if ((fp = fopen(pidfile, "w")) == NULL)
        err_exit("create pid file failed!");
    fwrite(pstr, 1024, sizeof(pid), fp);
    fclose(fp);
}

void path_init() {

    /* get pid file path */
    getcwd(fpath, sizeof(fpath));
    strcpy(pidfile, fpath);
    strcat(pidfile, "pid");
}

void aprs_init() {

    path_init();
    run_check();
    if(daemon_init("[aprs server]", LOG_DAEMON) != 0)
        err_exit("deamon init failed!");
    run_lock();
}

int main () {

    aprs_init();
    char recvbuf[MAXLINE];
    int serv;
    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(61591);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (bind(serv, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        err_exit("can not bind!");
    }
    while(1) {
        int num, pid, len;
        len = sizeof(cliaddr);
        num = recvfrom(serv, &recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &len);
        if ((pid == fork()) < 0)
            err_exit("handle new client failed!");
        else if (pid == 0)
            handle(recvbuf, &cliaddr);
    }
}
