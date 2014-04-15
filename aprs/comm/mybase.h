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

#include "mydaemon.h"
#include "myfun.h"
#include "mylog.h"
#include "mynet.h"
#include "mysig.h"

#define DATELEN 30

typedef unsigned short unit8_t;
typedef unsigned int unit32_t;
typedef unsigned long long unit64_t;

#endif
