/*************************************************************************
    > File Name: recom.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时07分48秒
 ************************************************************************/

#include <stdio.h>
#include "comm/mybase.h"

struct recom_info {

    unit32_t uid;
    unit32_t pid;
    unit8_t point1;
    unit8_t point2;
    unit8_t point3;
};

void get_recoms(unit32_t u_id, char *recoms) {

    strcpy(recoms, "1|32|52|23|23");
}

void save_recom(const char msg) {

}
