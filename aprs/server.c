/*************************************************************************
    > File Name: server.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时27分58秒
 ************************************************************************/

#include "comm/mybase.h"
#include "recom.h"
#include "init.h"

int serv;

/*
 * 0 : single
 * 1 : multiple progress
 * 2 : multiple thread
 * */
int run_mode = 0;

int is_debug = 1;

/* format get: 0|uid */
/* format set: 1|uid|pid|point1|point2|point3 */
int get_req_type(const char *msg) {

    int num = 0;
    num = get_char_num(msg, '|');
    if (num == 1)
        return 0;
    else if (num == 5)
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

void cli_handle(const char *msg, struct sockaddr_in *cliaddr, int clilen) {

    char tmp[100] = {0};
    if (is_debug) {
        sprintf(tmp, "new request receive!");
        log_info(tmp);
    }
    char resp[100] = {0};
    get_respon(msg, resp);
    int num = sendto(serv, resp, strlen(resp), 0, (struct sockaddr *)cliaddr, clilen);
    exit(0);
}

int main () {

    aprs_init(&run_mode);
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

        /* handle client request by different mode */
        if (run_mode == 0)
            cli_handle(recvbuf, &cliaddr, clilen);
        else if (run_mode == 1 || run_mode == 2) {
            if ((pid = fork()) < 0)
                err_exit("handle new client failed!");
            else if (pid == 0)
            cli_handle(recvbuf, &cliaddr, clilen);
        }
    }
}
