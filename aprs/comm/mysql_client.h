/*************************************************************************
    > File Name: mysql_client.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月15日 星期二 21时28分11秒
 ************************************************************************/

#ifndef _MYSQL_CLIENT_H_
#define _MYSQL_CLIENT_H_

#include "mybase.h"
#include <mysql/mysql.h>

#define MAX_COLUMN 100

MYSQL_RES* MYSQL_QUERY(const char *query);

int get_field_id(MYSQL_RES *res, const char *fname);

#endif
