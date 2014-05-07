/*************************************************************************
    > File Name: mysql_client.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月15日 星期二 21时27分53秒
 ************************************************************************/

#include "mysql_client.h"

const char my_mysql_host[] = "127.0.0.1";
const int my_mysql_port = 3306;
const char my_mysql_username[] = "root";
const char my_mysql_password[] = "root";
const char my_dbname[] = "aprs_test";
//const char my_dbname[] = "aprs";

MYSQL_RES* MYSQL_QUERY(const char *query) {

    MYSQL my_con;
    MYSQL_RES *result = NULL;
    mysql_init(&my_con);
    int res;
    if (mysql_real_connect(&my_con, my_mysql_host, my_mysql_username, my_mysql_password, my_dbname, my_mysql_port, NULL, 0)) {
        res = mysql_query(&my_con, query);
        if (!res) {
            result = mysql_store_result(&my_con);
        } else {
            log_err(mysql_error(&my_con));
        }
    } else {
        log_err("mysql connect error!");
    }
    mysql_close(&my_con);
    return result;
}

int get_field_id(MYSQL_RES *res, const char *fname) {

    MYSQL_FIELD *fd = NULL;
    char column[MAX_COLUMN][MAX_COLUMN];
    int field = 0;

    for (int i = 0; fd = mysql_fetch_field(res); ++i) {
        memset(column[i], 0, sizeof(column[i]));
        strcpy(column[i],fd->name);
    }

    field = mysql_num_fields(res);

    for (int i = 0; i < field; ++i) {
        if (!strcmp(column[i], fname))
            return i;
    }
    return -1;
}
