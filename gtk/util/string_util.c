//
// Created by yangkui on 2021/7/6.
//

#include <string.h>
#include "includes/string_util.h"

extern void* x_malloc(unsigned long size);

extern char *str_link(char *a, char *b) {
    unsigned long len = strlen(a) + strlen(b);
    char *link = x_malloc(len);
    strcat(link, a);
    strcat(link, b);
    return link;
}