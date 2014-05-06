/*************************************************************************
    > File Name: calcul.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年05月04日 星期日 16时59分17秒
 ************************************************************************/

#include "calcul.h"


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

void get_top_n(struct nb_info **top_list, double *sim_list, unit32_t p_index) {

    *top_list = malloc_zero(sizeof(struct nb_info) * TOP_N);

    struct nb_info *tail = *top_list + TOP_N - 1;
    if (IS_KMEANS) {
        unit32_t c_id = get_clus_index(p_index);
        for (unit32_t i = 0; i < clus_list[c_id].size; ++i) {
            unit32_t id = clus_list[c_id].p_list[i];
            struct nb_info *cmp = tail;
            while (cmp != *top_list - 1 && sim_list[id] > cmp->pearson) {
                struct nb_info tv = *cmp;
                struct nb_info new;
                new.p_index = id;
                new.pearson = sim_list[id];
                *cmp = new;
                if (cmp != tail)
                    *(cmp + 1) = tv;
                --cmp;
            }
        }
    } else {
        for (unit32_t i = 0; i < produced_count; ++i) {
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

        double *sim_list = malloc_zero(sizeof(double) * produced_count);

        /* calculate similarity one by one */
        double *tp = sim_list;
        if (IS_KMEANS) {
            unit32_t c_id = get_clus_index(p_index);
            for (unit32_t i = 0; i < clus_list[c_id].size; ++i) {
                if (clus_list[c_id].p_list[i] == p_index)
                    /* exclude itself */
                    *tp = -1;
                else
                    /* get pearson similarity */
                    *tp = get_pearson_similarity(p_index, clus_list[c_id].p_list[i]);
            }
        } else {
            for (int i = 0; i < produced_count; ++i) {
                if (i == p_index)
                    /* exclude itself */
                    *tp = -1;
                else
                    /* get pearson similarity */
                    *tp = get_pearson_similarity(p_index, i);
                ++tp;
            }
        }
        /* get top n neighbors by pearson value */
        get_top_n(neighbors, sim_list, p_index);

        /* set cache */
        set_neighbor_cache(p_index, *neighbors);

        /* free space */
        free(sim_list);
    }
}

double get_average_estimate(unit32_t p_index) {

    double sum = 0;
    for (int i = 0; i < user_count; ++i) {
        sum += get_point(i, p_index);
    }
    return sum / user_count;
}

double get_estimate(unit32_t u_id, unit32_t p_index) {

    /* get topN neighbor */
    struct nb_info *neighbors = NULL;
    get_neighbors(p_index, &neighbors);

    unit32_t u_index = get_u_index(u_id);

    /* calculate */
    int i = 0;
    struct nb_info *tp = neighbors;
    double numerator = 0;
    double denominator = 0;
    while (i < TOP_N) {
        if (tp->pearson == -1 || tp->pearson == 0)
            break;
        numerator += (get_point(u_index, tp->p_index) - get_average_estimate(tp->p_index)) * tp->pearson;
        denominator += tp->pearson;
        ++tp;
        ++i;
    }

    if (denominator == 0)
        return 0;
    else
        return get_average_estimate(p_index) + numerator / denominator;
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
#define RECOMMEND_N 20

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

    /* TODO */
}

const unit32_t calcul_u_num = 800;

const unit32_t calcul_p_num = 1000;

double mae_calcul() {

    double mae_final = 0;

    /* get start time */
    time_t start;
    time(&start);

    /* calculate */
    for (unit32_t u_id = 1; u_id < calcul_u_num; ++u_id) {
        double mae = 0;
        /* get one mae */
        for (unit32_t p_index = 0; p_index < calcul_p_num; ++p_index) {
            double t = get_estimate(u_id, p_index) - get_point(get_u_index(u_id), p_index);
            if (t < 0)
                t *= -1;
            mae += t / calcul_p_num;
        }
        mae_final += mae;
    }

    /* get final time */
    time_t end;
    time(&end);

    /* get running performance */
    double speed = (double) (end - start) / calcul_u_num;

    mae_final /= calcul_u_num;

    /* print mae final */
    char t_str[1024] = {0};
    sprintf(t_str, "final mae: %lf, speed:%lf", mae_final, speed);
    log_info(t_str);
}
