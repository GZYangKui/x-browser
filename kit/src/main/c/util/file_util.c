//
// Created by yangkui on 2021/7/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/file_util.h"

char *r_file(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("读取文件失败\n");
        return NULL;
    }
    int c;
    int pos = 0;
    int base = 100;
    char *content = malloc(sizeof(char) * base);
    while ((c = fgetc(file)) != -1) {
        if(pos>=base){
            base = base*2;
            content = realloc(content, base);
            if(content == NULL){
                printf("%s,新内存大小:%d","内存分配失败",base);
                return NULL;
            }
        }
        *(content + pos) = (char) c;
        pos++;
    }
    fclose(file);

    return content;
}