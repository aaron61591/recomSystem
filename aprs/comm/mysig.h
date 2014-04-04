/*************************************************************************
    > File Name: mysig.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月12日 星期三 14时46分16秒
 ************************************************************************/

#ifndef _MYSIG_H_
#define _MYSIG_H_

#include <stdio.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <signal.h>

typedef void sigfunc(int);

sigfunc *signal(int signo, sigfunc *func);

void sig_chld(int signo);

#endif
