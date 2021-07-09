//
// Created by yangkui on 2021/7/9.
//

#ifndef X_LITE_MEM_UTIL_H
#define X_LITE_MEM_UTIL_H
#include <stddef.h>
#include <stdlib.h>

/**
 * 释放堆上内存
 * @param pointer 待释放地址
 */
extern void x_free(void *pointer);
/**
 * 动态在堆上申请内存
 * @param size 所需内存大小,单位字节
 */
extern void *x_malloc(unsigned long size);

#endif //X_LITE_MEM_UTIL_H
