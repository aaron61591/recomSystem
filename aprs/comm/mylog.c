/*************************************************************************
    > File Name: mylog.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月04日 星期五 17时18分24秒
 ************************************************************************/

#include "mylog.h"

int get_log_fp() {

    return fileno(log_fp);
}

void log_close() {

    if (log_fp != NULL)
        fclose(log_fp);
}

void log_info(const char *info) {

    char date[DATELEN] = {0};
    get_current_time(date);
    fprintf(log_fp, "%s %d [info] %s\n", date, getpid(), info);
    fflush(log_fp);
}

void log_int(int n) {

    char tmp[1024] = {0};
    sprintf(tmp, "%d", n);
    log_info(tmp);
}

void log_warn(const char *warn) {

    char date[DATELEN] = {0};
    get_current_time(date);
    fprintf(log_fp, "%s %d [warn] %s\n", date, getpid(), warn);
    fflush(log_fp);
}

void log_err(const char *err) {

    char date[DATELEN] = {0};
    get_current_time(date);
    fprintf(log_fp, "%s %d [error] %s, errno:%d\n", date, getpid(), err, errno);
    fflush(log_fp);
}

void log_init(const char *fpath) {

    if (log_fp == NULL) {
        log_fp = fopen(fpath, "a");
        log_info("log initailized!");
    }
}
