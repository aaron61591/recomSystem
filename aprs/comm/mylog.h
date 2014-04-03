/*************************************************************************
    > File Name: mylog.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 21时43分53秒
 ************************************************************************/

#ifndef MYLOG
#include <stdio.h>

#define MAXLOG 1024

FILE *log_fp;

void log_init() {

    if (log_fp == NULL)
        log_fp = fopen("log", "a");
}

int get_log_fp() {

    return fileno(log_fp);
}

void log_close() {

    if (log_fp != NULL)
        fclose(log_fp);
}

void log_info(const char *info) {

    char date[DATELEN];
    fprintf(log_fp, "[info] %s %s\n", date, info);
}

void log_warn(const char *warn) {

    char date[DATELEN];
    fprintf(log_fp, "[warn] %s %s\n", date, warn);
}

void log_err(const char *err) {

    char date[DATELEN];
    fprintf(log_fp, "[error] %s %s, errno:%d\n", date, err, errno);
}

#endif
