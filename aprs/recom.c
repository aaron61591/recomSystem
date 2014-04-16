/*************************************************************************
    > File Name: recom.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月02日 星期三 10时07分48秒
 ************************************************************************/

#include "recom.h"
#include "data.h"

/* recom_matrix */
struct u_node *recom_matrix = NULL;

struct u_node* create_u_node (unit32_t u_id) {

    struct u_node *tmp = malloc(sizeof(struct u_node));
    tmp->u_id = u_id;
    tmp->hp = NULL;
    tmp->next = NULL;
    return tmp;
}

struct p_node* create_p_node (unit32_t p_id, unit8_t point) {

    struct p_node *tmp = malloc(sizeof(struct p_node));
    tmp->p_id = p_id;
    tmp->point = point;
    tmp->next = NULL;
    return tmp;
}

void append_p_node(struct u_node *up, struct p_node *pp) {

    if (up->hp == NULL) {
        up->hp = pp;
    } else {
        struct p_node *tmp = up->hp;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = pp;
    }
}

struct u_node* create_recom_matrix() {

    struct u_node *head;

    /* get orderly data */
    int num = 0;
    struct recom_info *dp = get_recom_info(&num);

    if (num == 0)
        return NULL;

    /* create matrix */
    struct u_node *up = NULL;
    struct p_node *pp = NULL;

    up = create_u_node(dp->u_id);
    pp = create_p_node(dp->p_id, dp->point);

    head = up;

    for (size_t i = 1; i < num; ++i) {
        ++dp;
        if (dp->u_id != up->u_id) {
            struct u_node *tmp = create_u_node(dp->u_id);
            up->next = tmp;
            up = tmp;
        }
        pp = create_p_node(dp->p_id, dp->point);
        append_p_node(up, pp);
    }

    /* free recom_info */
    while(0 != num--)
        free(dp++);
    return head;
}

void recom_init() {

    recom_matrix = create_recom_matrix();
}

void get_recoms(unit32_t u_id, char *recoms) {

    strcpy(recoms, "1|32|52|23|23");
}

void save_recom(const char *msg) {

    //TODO
}
