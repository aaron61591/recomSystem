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
        int size = sizeof(struct recom_info) * *num;
        struct recom_info *recom = malloc(size);
        memset(recom, 0, size);

        /* get field id*/
        int field_uid = get_field_id(res, "USER_ID");
        int field_pid = get_field_id(res, "PRO_ID");
        int field_point1 = get_field_id(res, "POINT1");
        int field_point2 = get_field_id(res, "POINT1");
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
            tmp.point1 = atoi(row[field_point1]);
            tmp.point2 = atoi(row[field_point2]);
            *tp = tmp;
            ++tp;
        }
        mysql_free_result(res);
        return recom;
    }

    return NULL;
}

unit32_t* get_user_list(int *user_count) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    unit32_t *user_list = NULL;

    res = MYSQL_QUERY("select ID from USER order by ID ASC");

    if (res != NULL) {

        /* get user_count */
        *user_count = mysql_num_rows(res);

        /* apply for space */
        int size = sizeof(unit32_t) * *user_count;
        user_list = malloc(size);
        memset(user_list, 0, size);

        /* get field id */
        int field_id = get_field_id(res, "ID");
        if (field_id == -1) {
            log_err("error field name!");
            return NULL;
        }

        unit32_t *tp = user_list;
        while (row = mysql_fetch_row(res)) {
            *tp = atoi(row[field_id]);
            ++tp;
        }

        mysql_free_result(res);
    }

    return user_list;
}

unit32_t* get_produced_list(int *produced_count) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    unit32_t *produced_list;

    res = MYSQL_QUERY("select ID from TRAVEL_INFO order by ID ASC");

    if (res != NULL) {

        /* get produced_count */
        *produced_count = mysql_num_rows(res);

        /* apply for space */
        int size = sizeof(unit32_t) * *produced_count;
        produced_list = malloc(size);
        memset(produced_list, 0, size);

        /* get field id */
        int field_id = get_field_id(res, "ID");
        if (field_id == -1) {
            log_err("error field name!");
            return NULL;
        }

        unit32_t *tp = produced_list;
        while (row = mysql_fetch_row(res)) {
            *tp = atoi(row[field_id]);
            ++tp;
        }

        mysql_free_result(res);
    }

    return produced_list;
}

void set_recom(unit32_t u_id, unit32_t p_id, unit8_t point) {

    //TODO
}
