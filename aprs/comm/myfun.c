/*************************************************************************
    > File Name: myfun.c
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2014年04月04日 星期五 17时04分40秒
 ************************************************************************/

#include "myfun.h"

void get_current_time(char *date) {

    time_t rawtime;
    char tstr[DATELEN] = {0};
    struct tm *now;
    int y, M, d, h, m, s;
    time(&rawtime);
    now = localtime(&rawtime);
    y = now->tm_year + 1900;
    M = now->tm_mon + 1;
    d = now->tm_mday;
    h = now->tm_hour;
    m = now->tm_min;
    s = now->tm_sec;
    sprintf(tstr, "%d-%d-%d %d:%d:%d\0", y, M, d, h, m, s);
    strcpy(date, tstr);
}

int max(int a, int b) {

    return a > b ? a : b;
}

int file_exist(const char *fname) {

    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL)
        return -1;
    fclose(fp);
    return 0;
}

int get_char_num(const char *str, char c) {

    int num;
    while(1) {
        if(str[num++] == c)
            ++num;
    }
    return num;
}
