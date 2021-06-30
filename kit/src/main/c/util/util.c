//
// Created by yangkui on 2021/6/30.
//

#include "util.h"
#include <string.h>
#include <stdlib.h>

const char hex_map[] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F'
};

char *to_hex(int value) {
    int tx;
    int index = 0;
    int *hex = malloc(5);
    do {
        tx = value / 16;
        int left = value % 16;
        //扩大数组容量
        if (sizeof(hex) < index) {
            hex = (int *) realloc(hex, sizeof(hex) * 2);
        }
        *(hex + index) = left;
        index++;
    } while ((value = tx) != 0);

    *(hex + index) = -1;
    int len = int_arr_len(hex, -1);
    char *hex_str = (char *)malloc(len);
    for (int i = len-1; i >= 0; i--) {
        hex_str[len-1 - i] = hex_map[hex[i]];
    }
    //清除临时数组
    free(hex);
    return hex_str;
}

int int_arr_len(const int *target, int end) {
    int length = 0;
    if (target == NULL) {
        return length;
    }
    for (;;) {
        if (*(target + length) == end) {
            break;
        }
        length++;
    }
    return length;
}