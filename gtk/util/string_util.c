//
// Created by yangkui on 2021/7/6.
//

#include "../include/string_util.h"

extern char *str_malloc_cpy(const char *src) {
    int16 len = strlen(src);
    char *str = (char *) x_malloc(len + 1);
    strcpy(str, src);
    return str;
}