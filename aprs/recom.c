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

/* user, produced list */
unit32_t *user_list = NULL, *produced_list = NULL;

/* user, produced index */
unit32_t *user_index = NULL, *produced_index = NULL;

/* max id */
unit32_t max_p_id = 0, max_u_id = 0;

/* user, produced count */
unit32_t user_count = 0, produced_count = 0;

/* neighbor cache */
struct nb_info **neighbor_cache = NULL;

void init_user() {

    /* select user all from db */
    user_list = get_user_list(&user_count);

    /* init user index */
    max_u_id = user_list[user_count - 1];
    user_index = malloc_zero(sizeof(unit32_t) * (max_u_id + 1));

    for (unit32_t i = 0; i < user_count; ++i) {
        unit32_t tmp_u = user_list[i];
        user_index[tmp_u] = i;
    }
}

void init_produced() {

    /* select produced all from db */
    produced_list = get_produced_list(&produced_count);

    /* init produced index */
    max_p_id = produced_list[produced_count - 1];
    produced_index = malloc_zero(sizeof(unit32_t) * (max_p_id + 1));

    for (unit32_t i = 0; i < produced_count; ++i) {
        unit32_t tmp_p = produced_list[i];
        produced_index[tmp_p] = i;
    }
}

/* the performance can be better */
int get_u_index(unit32_t u_id) {

    if (u_id > max_u_id)
        return 0;
    else
        return user_index[u_id];
}

/* the performance can be better */
int get_p_index(unit32_t p_id) {

    if (p_id > max_p_id)
        return 0;
    else
        return produced_index[p_id];
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
    unit32_t num;
    struct recom_info *recoms = get_recom_info(&num);

    if (IS_DEBUG) {
        struct recom_info *lp = recoms;
        log_info("===== get recom info =====");
        for (unit32_t i = 0; i < num; ++lp,++i){
            char tmp[100] = {0};
            sprintf(tmp, "user_id:%d,pro_id:%d,point1:%d,point2:%d", lp->u_id, lp->p_id, lp->point1, lp->point2);
            log_info(tmp);
        }
    }

    /* from source data to recommend matrix */
    struct recom_info *tp = recoms;
    unit32_t n = num;
    while (0 != n--) {
        set_point(get_u_index(tp->u_id), get_p_index(tp->p_id), tp->point1 + tp->point2);
        ++tp;
    }

    free(recoms);
}

void init_cache() {

    neighbor_cache = malloc_zero(sizeof(struct nb_info *) * produced_count);
}

void recom_refresh (int signo) {

    log_info("===== recom refreshing =====");

    free(user_list);
    free(user_index);
    free(produced_list);
    free(produced_index);
    free(recom_matrix);
    for (unit32_t i = 0; i < produced_count; ++i) {
        if (neighbor_cache[i] != NULL)
            free(neighbor_cache[i]);
    }

    /* re-init */
    recom_init();
}

void recom_init() {

    init_user();
    init_produced();
    init_recom_matrix();
    init_cache();

    if (IS_DEBUG) {
        for (unit32_t i = 0; i < user_count; ++i) {
            char *tstr = malloc_zero(sizeof(char) * (produced_count + 1) * 4);
            for (unit32_t j = 0; j < produced_count; ++j) {
                unit8_t tp = get_point(i, j);
                char tmp[4] = {0};
                sprintf(tmp, "%d ", tp);
                strcat(tstr, tmp);
            }
            log_info(tstr);
            free(tstr);
        }
    }

    /* refresh every REFRESH_TIME */
    signal(SIGALRM, recom_refresh);
    alarm(REFRESH_TIME);

    log_info("===== recommend initialized! =====");
}

unit32_t* get_signed_set(unit32_t p_index_x, unit32_t p_index_y, unit32_t *set_num) {

    /* apply for space */
    unit32_t size = sizeof(unit32_t) * user_count;
    unit32_t *set = malloc(size);
    memset(set, -1, size);

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

    if (set_num == 0) {
        free(set);
        return 0;
    }

    if (IS_DEBUG) {
        log_info("set is not null");
    }

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
        double r_x = get_point(*set, p_index_x++);
        double r_y = get_point(*set, p_index_y++);
        numerator += (r_x - ave_x) * (r_y - ave_y);
        denominator1 += (r_x - ave_x) * (r_x - ave_x);
        denominator2 += (r_y - ave_y) * (r_y - ave_y);
    }

    /* free space of set */
    free(set);

    if (IS_DEBUG) {
        char lt[1024] = {0};
        sprintf(lt, "n:%f,d1:%f,d2:%f", numerator, denominator1, denominator2);
        log_info(lt);
    }

    if (denominator1 == 0 || denominator2 == 0)
        return 0;
    else {
        double pearson = numerator / sqrt(denominator1 * denominator2);
        return pearson > 0 ? pearson : pearson * -1;
    }
}

/* topN neighbor */
#define TOP_N 10

void get_top_n(struct nb_info **top_list, double *sim_list) {

    *top_list = malloc_zero(sizeof(struct nb_info) * TOP_N);

    struct nb_info *tail = *top_list + TOP_N - 1;
    for (int i = 0; i < produced_count; ++i) {
        struct nb_info *cmp = tail;
        while (cmp != *top_list - 1 && sim_list[i] > cmp->pearson) {
            struct nb_info tv = *cmp;
            struct nb_info new;
            new.p_index = i;
            new.pearson = sim_list[i];
            *cmp = new;
            if (cmp != tail)
                *(cmp + 1) = tv;
            --cmp;
        }
    }
}


void set_neighbor_cache(unit32_t p_index, struct nb_info *neighbor) {

    neighbor_cache[p_index] = neighbor;
    if (IS_DEBUG)
        log_info("set cache");
}

struct nb_info * get_neighbor_cache(unit32_t p_index) {

    if (IS_DEBUG)
        log_info("get from cache");
    return neighbor_cache[p_index];
}

void get_neighbors(unit32_t p_index, struct nb_info **neighbors) {

    *neighbors = get_neighbor_cache(p_index);

    /* is cache ? */
    if (!*neighbors) {

        double *sim_list = malloc(sizeof(double) * produced_count);

        /* calculate similarity one by one */
        double *tp = sim_list;
        for (int i = 0; i < produced_count; ++i) {
            if (i == p_index)
            /* exclude itself */
                *tp = -1;
            else {
                /* get pearson similarity */
                *tp = get_pearson_similarity(p_index, i);
                if (IS_DEBUG) {
                    char tmp[1024] = {0};
                    sprintf(tmp, "pearson:%f", *tp);
                    log_info(tmp);
                }
            }
            ++tp;
        }

        /* get top n neighbors by pearson value */
        get_top_n(neighbors, sim_list);

        /* set cache */
        set_neighbor_cache(p_index, *neighbors);

        /* free space */
        free(sim_list);
    }
}

double get_estimate(unit32_t u_id, unit32_t p_index) {

    /* exclude the produced */
    if (get_point(get_u_index(u_id), p_index) != 0)
        return 0;

    /* get topN neighbor */
    struct nb_info *neighbors = NULL;
    get_neighbors(p_index, &neighbors);

    /* calculate */
    double estimate = 0;

    int i = 0;
    struct nb_info *tp = neighbors;
    while (i < TOP_N) {
        ++i;
        if (tp->pearson == -1 || tp->pearson == 0)
            break;
        estimate += get_point(get_u_index(u_id), tp->p_index) * tp->pearson;
        ++tp;
    }

    /* free space */
    //free(neighbors);

    return estimate / i;
}

double* get_estimate_list(unit32_t u_id) {

    /* apply space */
    double *est_list = malloc(sizeof(double) * produced_count);

    /* get estimate value one by one */
    double *tp = est_list;
    for (int i = 0; i < produced_count; ++i, ++tp) {
        *tp = get_estimate(u_id, i);
        if (IS_DEBUG) {
            char lt[1024] = {0};
            sprintf(lt, "estimate:%f", *tp);
            log_info(lt);
        }
    }

    return est_list;
}

/* the count will recommend */
#define RECOMMEND_N 10

void get_recommend_str(const double *estimate, char *recomm_str) {

    int recomms[RECOMMEND_N];
    memset(recomms, -1, sizeof(int) * RECOMMEND_N);

    unit32_t n = produced_count;

    int *tail = recomms + RECOMMEND_N - 1;

    for (unit32_t i = 0; i < produced_count; ++i) {
        int *cmp = tail;
        while (cmp != recomms - 1 && estimate[i] != 0 && estimate[i] > *cmp) {
            unit32_t tmp = *cmp;
            *cmp = i;
            if (cmp != tail)
                *(cmp + 1) = tmp;
            --cmp;
        }
    }

    for (unit32_t i = 0; i < RECOMMEND_N; ++i) {
        if (recomms[i] == -1)
            break;
        char t_pid[20];
        sprintf(t_pid, "%d", recomms[i]);
        strcat(recomm_str, t_pid);
        strcat(recomm_str, "|");
    }
}

void get_recoms(unit32_t u_id, char *recoms) {

    /* get produced estimate value list */
    double *estimate = get_estimate_list(u_id);

    /* get recommend string */
    get_recommend_str(estimate, recoms);

    /* free estimate list space */
    free(estimate);
}

void save_recom(const char *msg) {

    //TODO
}
