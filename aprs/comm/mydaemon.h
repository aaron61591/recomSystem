/*************************************************************************
    > File Name: mydaemon.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 15时22分49秒
 ************************************************************************/

#ifndef _MYDAEMON_H_
#define _MYDAEMON_H_

#include "mybase.h"
#include "mydaemon.h"

#define MAXFD 64

extern int daemon_proc;

int daemon_init(const char *pname, int facility);

#endif
