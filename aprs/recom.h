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

#define IS_KMEANS 1

/* user, produced list */
unit32_t *user_list, *produced_list;

/* user, produced index */
unit32_t *user_index, *produced_index;

/* max id */
unit32_t max_p_id, max_u_id;

/* user, produced count */
unit32_t user_count, produced_count;

/* neighbor cache */
struct nb_info **neighbor_cache;

/* cluster size */
enum {
    clus_size = 500
};

/* cluster num */
unit32_t clus_num;

/* cluster */
struct cluster {

    double *centre;
    unit32_t *p_list;
    unit32_t size;
};

/* cluster list */
struct cluster *clus_list;

/* cluster index list */
unit32_t *clus_index;

struct nb_info {

    unit32_t p_index;
    double pearson;
};

/* get cluster index */
unit32_t get_clus_index(unit32_t p_index);

/* set cluster index */
void set_clus_index(unit32_t p_index, unit32_t clus_index);

/* initialize recommender system */
void recom_init();

/* get point from matrix */
unit8_t get_point(unit32_t u_index, unit32_t p_index);

/* set point into matrix */
void set_point(unit32_t u_index, unit32_t p_index, unit8_t point);

/* get user's index*/
int get_u_index(unit32_t u_id);

#endif
