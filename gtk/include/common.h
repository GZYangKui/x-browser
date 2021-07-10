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

typedef unsigned long int16;

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

#endif //X_LITE_COMMON_H
