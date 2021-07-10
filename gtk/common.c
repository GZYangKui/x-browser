//
// Created by yangkui on 2021/7/9.
//

#include <time.h>
#include "include/common.h"

/**
 * 返回当前格式化日期字符串
 * @param str
 * @return
 */
static int16 c_time(string str, int16 len) {
    time_t t = time(NULL);
    strftime(str, len, "%Y-%m-%d %H:%M:%S", localtime((&t)));
    return sizeof(str);
}

static void log(f_string type, f_string log) {
    char str[50];
    c_time(str, 50);
    printf("%s %s %s\n", str, type, log);
}

extern void info(f_string text) {
    log(INFO, text);
}

extern void debug(f_string text) {
    log(DEBUG, text);
}

extern void error(f_string text) {
    log(ERROR, text);
}

extern void trace(f_string text) {
    log(TRACE, text);
}


extern void *x_malloc(int16 size) {
    void *pointer = (void *) malloc(size);
    memset(pointer, 0, size);
    printf("成功分配:%ld字节\n", size);
    return pointer;
}