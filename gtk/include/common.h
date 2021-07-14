//
// Created by yangkui on 2021/7/10.
//

#ifndef X_LITE_COMMON_H
#define X_LITE_COMMON_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/************默认窗口宽度和高度************/
#define DEFAULT_WINDOW_WIDTH 400
#define DEFAULT_WIDOW_HEIGHT 700

/******日志输出等级*******/
#define INFO "INFO"
#define DEBUG "DEBUG"
#define ERROR "ERROR"
#define TRACE "TRACE"

/**释放堆上内存**/
#define X_FREE(p) free((void *)p); \
        p = NULL

typedef unsigned long int16;

typedef char *string;
typedef const char *f_string;


extern void info(f_string text);

extern void debug(f_string text);

extern void error(f_string text);

extern void trace(f_string text);

/**
 * 动态在堆上申请内存
 * @param size 所需内存大小,单位字节
 */
extern void *x_malloc(int16 size);

#endif //X_LITE_COMMON_H
