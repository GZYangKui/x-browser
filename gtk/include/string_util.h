//
// Created by yangkui on 2021/7/6.
//

#ifndef X_LITE_STRING_UTIL_H
#define X_LITE_STRING_UTIL_H

#include "common.h"

/**
 * 通过malloc方式拷贝字符串
 * @param str 待拷贝字符串
 * @return 返回拷贝后的字符串
 */
extern char *str_malloc_cpy(const char *src);

#endif //X_LITE_STRING_UTIL_H
