/*************************************************************************
    > File Name: myfun.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年03月16日 星期日 12时13分57秒
 ************************************************************************/

#ifndef _MYFUN_H_
#define _MYFUN_H_

#include <time.h>
#include "mybase.h"

void get_current_time(char *date);

int max(int a, int b);

int file_exist(const char *fname);

int get_char_num(const char *str, char c);

void free_multi(void *p, size_t num);

void* malloc_zero(int size);

#endif
