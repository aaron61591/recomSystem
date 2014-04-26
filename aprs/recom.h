/*************************************************************************
    > File Name: recom.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月15日 星期二 16时21分32秒
 ************************************************************************/
#ifndef _RECOM_H_
#define _RECOM_H_


#include "comm/mybase.h"

#define REFRESH_TIME 15 * 60

struct nb_info {

    unit32_t p_index;
    double pearson;
};

void recom_init();

void get_recoms(unit32_t u_id, char *recoms);

void save_recom(const char *msg);

#endif
