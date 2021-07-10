//
// Created by yangkui on 2021/7/5.
//

#include "../include/file_util.h"

char *r_file(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        error("读取文件失败");
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
                error("内存分配失败");
                return NULL;
            }
        }
        *(content + pos) = (char) c;
        pos++;
    }
    fclose(file);

    return content;
}