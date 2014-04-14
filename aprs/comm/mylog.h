/*************************************************************************
    > File Name: mylog.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 21时43分53秒
 ************************************************************************/

#ifndef _MYLOG_H_
#define _MYLOG_H_

#include <stdio.h>
#include "mybase.h"

#define MAXLOG 1024

FILE *log_fp;

int get_log_fp();

void log_close();

void log_info(const char *info);

void log_int(int n);

void log_warn(const char *warn);

void log_err(const char *err);

void log_init(const char *fpath);

#endif
