//
// Created by yangkui on 2021/7/6.
//

#include "../include/string_util.h"

extern char *str_link(char *a, char *b) {
    //预留一位结束位
    unsigned long len = strlen(a) + strlen(b)+1;
    char *link = x_malloc(len);
    strcat(link, a);
    strcat(link, b);
    return link;
}