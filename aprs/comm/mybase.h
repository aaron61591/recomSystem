/*************************************************************************
    > File Name: mybase.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月16日 星期日 12时13分57秒
 ************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int daemon_proc;

int max(int a, int b) {
    return a > b ? a : b;
}

void err_exit(const char *msg) {

    if (daemon_proc) {
        syslog(3, "%s\nerrno:%d\n", msg, errno);
    } else {
        printf("%s\nerrno:%d\n", msg, errno);
        exit(-1);
    }
}

void fin_exit(const char *msg) {

    if (daemon_proc) {
        syslog(6, "%s\n", msg);
    } else {
        printf("%s\n", msg);
        exit(0);
    }
}

int file_exist(const char *fname) {

    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL)
        return -1;
    else
        return 0;
}
