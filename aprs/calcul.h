/*************************************************************************
    > File Name: calcul.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年05月04日 星期日 16时56分54秒
 ************************************************************************/

#ifndef _CALCUL_H_
#define _CALCUL_H_

#include "comm/mybase.h"
#include "recom.h"

/* get recoms data for u_id */
void get_recoms(unit32_t u_id, char *recoms);

/* this function is not necessary */
void save_recom(const char *msg);

/* calcul mea value for forecast */
double mea_calcul();

#endif
