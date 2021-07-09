//
// Created by yangkui on 2021/7/9.
//

#include <memory.h>
#include "includes/mem_util.h"

extern void x_free(void *pointer) {
    if (pointer == NULL) {
        return;
    }
    free(pointer);
    pointer = NULL;
}

extern void *x_malloc(unsigned long size) {
    void *pointer = (void *) malloc(size);
    memset(pointer, 0, size);
    return pointer;
}