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
    unit8_t point;
};


struct recom_info * get_recom_info(int *num);

void set_recom(unit32_t u_id, unit32_t p_id, unit8_t point);

#endif
