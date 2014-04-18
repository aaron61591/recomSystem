/*************************************************************************
    > File Name: data.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月15日 星期二 16时39分21秒
 ************************************************************************/

#ifndef _DATA_H_
#define _DATA_H_

#include "comm/mybase.h"

struct recom_info {

    unit32_t u_id;
    unit32_t p_id;
    unit8_t point1;
    unit8_t point2;
};

struct recom_info * get_recom_info(int *num);

unit32_t* get_user_list(int *user_count);

unit32_t* get_produced_list(int *produced_count);

void set_recom(unit32_t u_id, unit32_t p_id, unit8_t point);

#endif
