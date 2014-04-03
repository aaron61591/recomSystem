/*************************************************************************
    > File Name: mybase.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月16日 星期日 12时13分57秒
 ************************************************************************/

#ifndef MYBASE

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DATELEN 25

#include "mylog.h"

int daemon_proc;
int fd;

int max(int a, int b) {
    return a > b ? a : b;
}

void set_log(int log) {

    fd = log;
}

void err_exit(const char *msg) {

    if (fd != 0) {
        log_err(msg);
    } else if (daemon_proc)
        syslog(3, "%s\nerrno:%d\n", msg, errno);
    else
        printf("%s\nerrno:%d\n", msg, errno);
    exit(-1);
}

void fin_exit(const char *msg) {

    if (fd != 0) {
        log_info(msg);
    } else if (daemon_proc)
        syslog(6, "%s\n", msg);
    else
        printf("%s\n", msg);
    exit(0);
}

int file_exist(const char *fname) {

    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL)
        return -1;
    fclose(fp);
    return 0;
}

void get_current_time(char *date) {

    time_t rawtime;
    char tstr[DATELEN];
    struct tm *now;
    int y, M, d, h, m, s;
    time(&rawtime);
    now = localtime(&rawtime);
    y = now->tm_year + 1990;
    M = now->tm_mon + 1;
    d = now->tm_mday;
    h = now->tm_hour;
    m = now->tm_min;
    s = now->tm_sec;
    sprintf(tstr, "%d-%d-%d %d:%d:%d", y, M, d, h, m, s);
    strcpy(date, tstr);
}

#endif
