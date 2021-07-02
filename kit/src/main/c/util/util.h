//
// Created by yangkui on 2021/6/30.
//

#ifndef X_LITE_UTIL_H

/**
 *
 * 十进制转换十六进制
 */
extern char *to_hex(int value);

/**
 * 十六进制转换为十进制
 */
extern int hex_to_natual(char *hex);

/**
 * 计算数组长度
 *
 * @param end 结束符号
 * @param target 目标数组
 *
 */
extern int int_arr_len(const int *target, int end);

#define X_LITE_UTIL_H
#endif //X_LITE_UTIL_H
