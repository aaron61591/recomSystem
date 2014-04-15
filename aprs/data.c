/*************************************************************************
    > File Name: data.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时10分38秒
 ************************************************************************/

#include "data.h"

/* temporary data */
struct recom_info * get_recom_info(int *num) {

    size_t info_num = 6;
    *num = info_num;
    struct recom_info *recom = malloc(sizeof(struct recom_info) * info_num);
    struct recom_info tmp;

    /* data detail */
    tmp.u_id = 1;
    tmp.p_id = 1;
    tmp.point = 1;
    recom[0] = tmp;
    tmp.u_id = 1;
    tmp.p_id = 3;
    tmp.point = 3;
    recom[1] = tmp;
    tmp.u_id = 3;
    tmp.p_id = 2;
    tmp.point = 3;
    recom[2] = tmp;
    tmp.u_id = 3;
    tmp.p_id = 3;
    tmp.point = 4;
    recom[3] = tmp;
    tmp.u_id = 5;
    tmp.p_id = 1;
    tmp.point = 2;
    recom[4] = tmp;
    tmp.u_id = 5;
    tmp.p_id = 2;
    tmp.point = 1;
    recom[5] = tmp;

    return recom;
}

void set_recom(unit32_t u_id, unit32_t p_id, unit8_t point) {

    //TODO
}
