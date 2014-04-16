/*************************************************************************
    > File Name: data.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时10分38秒
 ************************************************************************/

#include "data.h"
#include "comm/mysql_client.h"

struct recom_info * get_recom_info(int *num) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW row;

    res = MYSQL_QUERY("select * from RECOM order by USER_ID ASC");
    if (res != NULL) {

        /* get row num */
        *num = mysql_num_rows(res);

        /* apply for space */
        struct recom_info *recom = malloc(sizeof(struct recom_info) * *num);

        /* get field id*/
        int field_uid = get_field_id(res, "USER_ID");
        int field_pid = get_field_id(res, "PRO_ID");
        int field_point = get_field_id(res, "POINT");
        if (field_uid == -1 || field_pid == -1 || field_uid == -1) {
            log_err("field name error");
            return NULL;
        }

        /* get detail data*/
        struct recom_info *tp = recom;
        while (row = mysql_fetch_row(res)) {
            struct recom_info tmp;
            tmp.u_id = atoi(row[field_uid]);
            tmp.p_id = atoi(row[field_pid]);
            tmp.point = atoi(row[field_point]);
            *tp = tmp;
            ++tp;
        }
        mysql_free_result(res);
        return recom;
    }

    return NULL;
    /* data for test */
    /*
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
    */

}

void set_recom(unit32_t u_id, unit32_t p_id, unit8_t point) {

    //TODO
}
