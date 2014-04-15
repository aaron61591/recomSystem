/*************************************************************************
    > File Name: recom.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月15日 星期二 16时21分32秒
 ************************************************************************/
#ifndef _RECOM_H_
#define _RECOM_H_

#include "comm/mybase.h"

struct u_node {

    unit32_t u_id;
    struct p_node *hp;
    struct u_node *next;
};

struct p_node {

    unit32_t p_id;
    unit8_t point;
    struct p_node *next;
};

void recom_init();

void get_recoms(unit32_t u_id, char *recoms);

void save_recom(const char *msg);

#endif
