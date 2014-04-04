/*************************************************************************
    > File Name: myexit.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月04日 星期五 17时45分03秒
 ************************************************************************/

#include "myexit.h"

int fd = -1;

int daemon_proc;

void set_log(int log) {

    fd = log;
}

void err_exit(const char *msg) {

    if (fd >= 0) {
        log_err(msg);
    } else if (daemon_proc)
        syslog(3, "%s\nerrno:%d\n", msg, errno);
    else
        printf("%s\nerrno:%d\n", msg, errno);
    exit(-1);
}

void fin_exit(const char *msg) {

    if (fd >= 0) {
        log_info(msg);
    } else if (daemon_proc)
        syslog(6, "%s\n", msg);
    else
        printf("%s\n", msg);
    exit(0);
}


