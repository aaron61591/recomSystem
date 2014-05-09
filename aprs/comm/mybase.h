/*************************************************************************
    > File Name: mybase.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月04日 星期五 18时12分22秒
 ************************************************************************/

#ifndef _MYBASE_H_
#define _MYBASE_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>

typedef unsigned long long unit64_t;
typedef unsigned short unit8_t;
typedef unsigned int unit32_t;

#include "myexit.h"
#include "mylog.h"
#include "mydaemon.h"
#include "myfun.h"
#include "mynet.h"
#include "mysig.h"

#define DATELEN 30

/* if debug mode (print debug log) */
#define IS_DEBUG 1

#endif
