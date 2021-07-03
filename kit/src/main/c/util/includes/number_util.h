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

/**
 *
 * 生成指定区间随机数
 * @param star 区间起始
 * @param end 区间结束
 * @return  返回随机数字
 */
extern int num_r(int start, int end);

#define RANDOM (-1.0+2.0*(double)rand()/RAND_MAX)

#define X_LITE_UTIL_H
#endif //X_LITE_UTIL_H
