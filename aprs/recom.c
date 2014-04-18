/*************************************************************************
    > File Name: recom.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时07分48秒
 ************************************************************************/

#include "recom.h"
#include "data.h"

/* recom_matrix */
unit8_t *recom_matrix = NULL;

/* user, produced index list */
unit32_t *user_list = NULL, *produced_list = NULL;

/* user, produced count */
unit32_t user_count = 0, produced_count = 0;

void init_user_index() {

    /* select user all from db */
    user_list = get_user_list(&user_count);
}

void init_produced_index() {

    /* select produced all from db */
    produced_list = get_produced_list(&produced_count);
}

/* the performance can be better */
int get_u_index(unit32_t u_id) {

    int n = 0;
    while (n != user_count) {
        if (user_list[n] == u_id)
            return n;
        ++n;
    }

    return -1;
}

/* the performance can be better */
int get_p_index(unit32_t p_id) {

    int n = 0;
    while (n != produced_count) {
        if (produced_list[n] == p_id)
            return n;
        ++n;
    }

    return -1;
}

unit8_t get_point(unit32_t u_index, unit32_t p_index) {

    unit8_t *tp = recom_matrix;
    tp += u_index * produced_count + p_index;
    return *tp;
}

void set_point(unit32_t u_index, unit32_t p_index, unit8_t point) {

    unit8_t *tp = recom_matrix;
    tp += u_index * produced_count + p_index;
    *tp = point;
}

void init_recom_matrix() {

    /* apply space */
    recom_matrix = malloc_zero(sizeof(unit8_t) * user_count * produced_count);

    /* get recom source data from mysql db */
    int num;
    struct recom_info *recoms = get_recom_info(&num);

    /* from source data to recommend matrix */
    struct recom_info *tp = NULL;
    while (0 != num--) {
        tp = recoms;
        set_point(get_u_index(tp->u_id), get_p_index(tp->p_id), tp->point1 + tp->point2);
    }
}

void recom_init() {

    init_user_index();
    init_produced_index();
    init_recom_matrix();
    log_info("recommend core initialized!");
}

unit32_t* get_signed_set(unit32_t p_index_x, unit32_t p_index_y, unit32_t *set_num) {

    /* apply for space */
    unit32_t *set = malloc(sizeof(unit32_t) * user_count);

    unit32_t *tp = set;
    for (int i = 0; i < user_count; ++i) {
        if (get_point(i, p_index_x) && get_point(i, p_index_y)) {
            *tp = i;
            ++tp;
            *set_num += 1;
        }
    }

    return set;
}

double get_pearson_similarity (unit32_t p_index_x, unit32_t p_index_y) {

    /* find the set which be signed by both x and y */
    unit32_t set_num = 0;
    unit32_t *set = get_signed_set(p_index_x, p_index_y, &set_num);

    if (set_num == 0)
        return 0;

    /* get average value */
    double sum_x = 0, sum_y = 0;
    unit32_t tmp = set_num;
    unit32_t *tp = set;
    while (0 != tmp--) {
        sum_x += get_point(*tp, p_index_x);
        sum_y += get_point(*tp, p_index_y);
        ++tp;
    }
    double ave_x = sum_x / set_num;
    double ave_y = sum_y / set_num;

    /* calculate pearson */
    double numerator = 0, denominator1 = 0, denominator2 = 0;
    tmp = set_num;
    while (0 != tmp--){
        double r_x = get_point(*set, p_index_x);
        double r_y = get_point(*set, p_index_y);
        numerator += r_x * r_x - r_x * ave_y - ave_x * r_y + ave_x * ave_y;
        denominator1 += r_x * r_x - 2 * r_x * ave_x + ave_x * ave_x;
        denominator2 += r_y * r_y - 2 * r_y * ave_y + ave_y * ave_y;
    }

    /* free space of set */
    free_multi(set, user_count);

    return numerator / sqrt(denominator1 * denominator2);
}

/* topN neighbor */
size_t top_n = 10;

unit32_t* get_top_n(unit32_t *sim_list) {

    /* apply space */
    unit32_t *top_list = malloc_zero(sizeof(unit32_t) * top_n);

    unit32_t *tail = top_list + top_n - 1;
    for (int i = 0; i < produced_count; ++i) {
        unit32_t *cmp = tail;
        while (cmp != top_list - 1 && sim_list[i] > *cmp) {
            unit32_t tv = *cmp;
            *cmp = i;
            if (cmp > tail)
                *(cmp + 1) = tv;
            --cmp;
        }
    }
}

unit32_t* get_neighbors(unit32_t p_index) {

    /* apply space */
    int *sim_list = malloc(sizeof(int) * produced_count);

    /* calculate similarity one by one */
    int *tp = sim_list;
    for (int i = 0; i < produced_count; ++i) {
        if (i == p_index)
        /* exclude itself */
            *tp = -1;
        else {
            /* get pearson similarity */
            *tp = get_pearson_similarity(p_index, i)
        }
        ++tp;
    }

    /* free space */
    free_multi(sim_list, sizeof(int) * produced_count);

    /* get top n neighbors by pearson value */
    return get_top_n(sim_list);
}

unit8_t* get_estimate(unit32_t u_id, unit32_t p_index) {

    /* get topN neighbor */
    unit32_t *neighbors = get_neighbors(p_index);

    // TODO
}

unit8_t* get_estimate_list(unit32_t u_id) {

    /* apply space */
    unit8_t *est_list = malloc(sizeof(unit8_t) * produced_count);

    /* get estimate value one by one */
    unit8_t *tp = est_list;
    for (int i = 0; i < produced_count; ++i) {
        *tp = get_estimate(u_id, i);
    }
}

const char* get_recommend_str(unit8_t *estimate) {

    // TODO
    return NULL;
}

void get_recoms(unit32_t u_id, char *recoms) {

    /* get produced estimate value list */
    unit8_t *estimate = get_recoms(u_id);

    /* get recommend string */
    strcpy(recoms, get_recommend_str(estimate));

    /* free estimate list space */
    free_multi(estimate, produced_count);
}

void save_recom(const char *msg) {

    //TODO
}
