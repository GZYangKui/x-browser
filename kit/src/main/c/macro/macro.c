//
// Created by yangkui on 2021/7/3.
//

#include <stdio.h>
#include "macro.h"

int main(int argc,char ** argv){
    {
        int a = 10;
        int b = 20;
        int c = SUB(a,b);
        printf("a-b=%d\n",c);
    }

    {
        int a = 30;
        int b = -60;
        int c = DISTANCE(a,b);
        printf("a与b的距离=%d\n",c);
    }
}