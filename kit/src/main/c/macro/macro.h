//
// Created by yangkui on 2021/7/3.
//

#ifndef X_LITE_MACRO_H
#define X_LITE_MACRO_H

/**
 * 定义一个宏 做两数相减
 */
#define SUB(a, b) (a-b)
/**
 * 定义文本中出现的形参应该使用括号括起来,这样确保实参是够表达式都能正确计算
 */
#define DISTANCE(x, y) ((x)>=(y)?(x)-(y):(y)-(x))

#endif //X_LITE_MACRO_H
