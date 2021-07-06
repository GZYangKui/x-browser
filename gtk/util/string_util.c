//
// Created by yangkui on 2021/7/6.
//

#include <malloc.h>
#include <string.h>
#include "includes/string_util.h"


extern char *str_link(char *a, char *b) {
    unsigned long len = strlen(a) + strlen(b) - 1;
    char *link = malloc(len);
    memset(link, 0, len);
    strcat(link, a);
    strcat(link, b);
    return link;
}