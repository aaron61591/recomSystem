/*************************************************************************
    > File Name: netcommon.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月11日 星期二 14时49分34秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAXLINE 1024

ssize_t writen(int fd, const void *ptr, size_t n) {

    size_t left;
    ssize_t written;
    left = n;
    while(left > 0) {
        if ((written = write(fd, ptr, left)) <= 0) {
            if(written < 0 && errno == EINTR)
                written = 0;
            else
                return(-1);
        }
        left -= written;
        ptr += written;
    }
    return(n);
}

ssize_t readn(int fd, void *ptr, size_t n) {
    size_t left;
    ssize_t nread;
    left = n;
    while(left > 0) {
        if ((nread = read(fd, ptr, left)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return(-1);
        } else if (nread == 0)
            break;
        left -= nread;
        ptr += nread;
    }
    return(n - left);
}

ssize_t readline(int fd, void *vptr, size_t n){

    ssize_t i, rc;
    char c;
    char *ptr = vptr;
    for (i = 1; i < n; i++){
again:
        if ((rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            return(i - 1);
        } else {
            if (errno == EINTR)
                goto again;
            return(-1);
        }
    }
    return(i);
}
