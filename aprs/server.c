/*************************************************************************
    > File Name: server.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时27分58秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include "comm/mybase.h"
#include "comm/mynet.h"

char fpath[50] = {0};
char pidpath[50] = {0};
char logpath[50] = {0};

int serv;

int is_debug = 1;

/* format set:uid|pid|point1|point2|point3 */
/* format get:uid */
int get_req_type(const char *msg) {

    int num;
    num = get_char_num(msg, '|');
    if (num == 0)
        return 0;
    else if (num == 4)
        return 1;
    else
        return -1;
}

void get_respon(const char *msg, char *resp) {

    int type = get_req_type(msg);
    if (type == 0) {
        /* get recommendation */
        get_recoms(atoi(msg), resp);
    } else if(type == 1) {
        /* save useraction */
        save_recom(msg);
        strcpy(resp, "ok");
    } else if(type == -1) {
        strcpy(resp, "invalid");
    }
}

void cli_handle(char *msg, struct sockaddr_in *cliaddr, int clilen) {

    if (is_debug) {
        char tmp[50];
        sprintf(tmp, "new request receive!");
        log_info(tmp);
    }
    char resp[100] = {0};
    get_respon(msg, resp);
    sendto(serv, resp, sizeof(resp), 0, (struct sockaddr *)cliaddr, clilen);
    exit(0);
}

void run_check() {

    if (file_exist(pidpath) == 0)
        err_exit("aprs is already running now!");
}

void run_lock() {

    FILE *fp;
    int pid = getpid();
    char pstr[5];
    memset(pstr, 0, sizeof(pstr));
    sprintf(pstr, "%d", pid);
    if ((fp = fopen(pidpath, "w")) == NULL)
        err_exit("create pid file failed!");
    fwrite(pstr, sizeof(pstr), 1, fp);
    fclose(fp);
}

void path_init() {

    /* get pid file path */
    getcwd(fpath, sizeof(fpath));
    strcpy(pidpath, fpath);
    strcat(pidpath, "/pid");
    strcpy(logpath, fpath);
    strcat(logpath, "/log");
}

void sig_chld(int signo) {

    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)
) > 0){
        printf("child %d terminated\n", pid);
    }
    return;
}

void aprs_init() {

    path_init();

    /* run lock */
    run_check();

    /* daemon running */
    if(daemon_init("[aprs server]", LOG_DAEMON) != 0)
        err_exit("deamon init failed!");
    run_lock();

    /* log initialize */
    log_init(logpath);
    set_log(get_log_fp());

    /* handle son process */
    signal(SIGCHLD, sig_chld);
}

int main () {

    aprs_init();
    char recvbuf[MAXLINE];
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
        int num, pid, clilen;
        clilen = sizeof(cliaddr);
        num = recvfrom(serv, &recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &clilen);
        if ((pid = fork()) < 0)
            err_exit("handle new client failed!");
        else if (pid == 0)
            cli_handle(recvbuf, &cliaddr, clilen);
    }
}
