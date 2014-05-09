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

unit32_t *user_list = NULL, *produced_list = NULL;

unit32_t *user_index = NULL, *produced_index = NULL;

unit32_t max_p_id = 0, max_u_id = 0;

unit32_t user_count = 0, produced_count = 0;

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
unit32_t get_u_index(unit32_t u_id) {

    if (u_id > max_u_id)
        return 0;
    else
        return user_index[u_id];
}

/* the performance can be better */
unit32_t get_p_index(unit32_t p_id) {

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
    if (IS_KMEANS) {
        free(clus_index);
        for (unit32_t i = 0; i < clus_num; ++i) {
            struct cluster clus = clus_list[i];
            free(clus.centre);
            free(clus.p_list);
        }
        free(clus_list);
    }
    for (unit32_t i = 0; i < produced_count; ++i) {
        if (neighbor_cache[i] != NULL)
            free(neighbor_cache[i]);
    }

    /* re-init */
    recom_init();
}

double get_distance(struct cluster *clus, unit32_t p_index) {

    double dis = 0;
    for(unit32_t i = 0; i < user_count; ++i) {
        double t = get_point(i, p_index) - clus->centre[i];
        dis += t * t;
    }
    return sqrt(dis);
}

unit8_t update_centre(double *centre, double *new_centre) {

    unit8_t is_change = 0;
    for (unit32_t i = 0; i < user_count; ++i) {
        if (centre[i] != new_centre[i]) {
            centre[i] = new_centre[i];
            is_change = 1;
        }
    }
    return is_change;
}

unit32_t get_clus_index(unit32_t p_index) {

    return clus_index[p_index];
}

void set_clus_index(unit32_t p_index, unit32_t c_id) {

    clus_index[p_index] = c_id;
}

void init_kmeans() {

    /* calculate the cluster num */
    clus_num = ceil((double) produced_count / clus_size);

    clus_list = malloc_zero(sizeof(struct cluster) * clus_num);

    /* initialize cluster */
    for (unit32_t i = 0; i < clus_num; ++i) {

        struct cluster clus;

        clus.centre = malloc_zero(sizeof(double) * user_count);
        for (unit32_t j = 0; j < user_count; ++j) {
            clus.centre[j] = get_point(j, i);
        }

        unit32_t size = sizeof(unit32_t) * produced_count;
        clus.p_list = malloc(size);
        memset(clus.p_list, -1, size);

        clus.size = 0;

        clus_list[i] = clus;

        /* initialize cluster index list */
        clus_index = malloc_zero(sizeof(unit32_t) * produced_count);
    }

    /* clustering */
    while (1) {

        /* reset cluster size */
        for (unit32_t i = 0; i < clus_num; ++i)
            clus_list[i].size = 0;

        /* select cluster */
        for (unit32_t i = 0; i < produced_count; ++i) {
            double dis = -1;
            unit32_t max_close = 0;
            for (unit32_t j = 0; j < clus_num; ++j) {
                double t_dis = get_distance(&clus_list[j], i);

                if (dis == -1 || t_dis < dis) {
                    dis = t_dis;
                    max_close = j;
                }
            }
            clus_list[max_close].p_list[clus_list[max_close].size] = i;
            /* set cluster index */
            set_clus_index(i, max_close);
            ++clus_list[max_close].size;
        }

        /* calculate new centre */
        unit8_t is_change = 0;
        for (unit32_t n = 0; n < clus_num; ++n) {
            struct cluster clus = clus_list[n];
            /* temporary space for new centre */
            double *new_centre = malloc_zero(sizeof(double) * user_count);
            for (unit32_t i = 0; i < clus.size; ++i) {
                for (unit32_t j = 0; j < user_count; ++j) {
                    new_centre[j] += (double) get_point(j, clus.p_list[i]) / clus.size;
                    }
                }

            if (update_centre(clus.centre, new_centre))
                is_change = 1;
            free(new_centre);
        }

        /* finish when all cluster's centre do not change */
        if (is_change == 0)
            break;
    }

    /* print clus size */
    for (unit32_t i = 0; i < clus_num; ++i) {
        struct cluster clus = clus_list[i];
        char tmp[1024] = {0};
        sprintf(tmp, "clus: %d, size: %d", i, clus.size);
        log_info(tmp);
    }

}

double mae_calcul();

void recom_init() {

    init_user();
    init_produced();
    init_recom_matrix();
    init_cache();

    if (IS_KMEANS)
        init_kmeans();

    /* MAE caculate */
    if (IS_MAE) {
        double mae = mae_calcul();
        char maestr[10] = {0};
        sprintf(maestr, "%f", mae);
        log_info(maestr);
    }

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

