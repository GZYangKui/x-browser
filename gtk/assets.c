//
// Created by yangkui on 2021/7/6.
//

#include "include/assets.h"
#include "include/string_util.h"

char *root_path = NULL;
char *img_path = "/assets/img/";


extern int16 project_path(char *buf, int size) {
    char *dir = getcwd(buf, size);
    if (dir == NULL) {
        return -1;
    }
    int16 len = strlen(dir);
    if (_ENV == DEV) {
        for (int16 i = len - 1; i >= 0; --i) {
            char c = *(dir + i);
            if (c == '/') {
                len = i + 1;
                break;
            } else {
                *(dir + i) = '\0';
            }
        }
    }
    return len;
}

extern GdkPixbuf *new_pix_buf_from_resource(char *id) {
    GError *err = NULL;
    GdkPixbuf *pb = gdk_pixbuf_new_from_resource(id, &err);
    if (err != NULL) {
        printf("加载资源文件失败:%s\n", err->message);
    }
    return pb;
}



