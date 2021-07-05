//
// Created by yangkui on 2021/7/3.
//

#ifndef X_LITE_MACRO_H

#include <math.h>

#define X_LITE_MACRO_H

/**
 * 定义一个宏 做两数相减
 */
#define SUB(a, b) (a-b)
/**
 * 定义文本中出现的形参应该使用括号括起来,这样确保实参是够表达式都能正确计算
 */
#define DISTANCE(x, y) ((x)>=(y)?(x)-(y):(y)-(x))

/**
 * 可选参数宏
 */
#define LOG(...) fprintf(stdout,__VA_ARGS__)

/**
 *
 * 字符串化运算符
 *
 */
#define printDSL(exp) printf(#exp "=%.2f\n" ,exp )

#define showArgs(...) puts(#__VA_ARGS__);

#define TEXT_A "Hello, world!"

#define msg(x) puts(TEXT_##x)


#endif //X_LITE_MACRO_H
