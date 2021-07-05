//
// Created by yangkui on 2021/7/3.
//

#include <stdio.h>
#include "macro.h"

int main(int argc, char **argv) {
    {
        int a = 10;
        int b = 20;
        int c = SUB(a, b);
        printf("a-b=%d\n", c);
    }

    {
        int a = 30;
        int b = -60;
        int c = DISTANCE(a, b);
        printf("a与b的距离=%d\n", c);
    }

    {
        //可变参数宏
        LOG("当前函数名称=%s\n", __func__);
    }

    {
        printDSL(5 * 2.0);
        showArgs(one\n, "2\n", three)
    }

    {
        msg(A);
    }
    printf("重定义前:%f\n", M_PI);
    //重定义宏
#undef M_PI
#define M_PI 3.1415926

    printf("重定义后=%f\n", M_PI);

    return 0;
}