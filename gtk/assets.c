//
// Created by yangkui on 2021/7/6.
//

#include "include/assets.h"
#include "util/includes/string_util.h"

char *root_path = NULL;
char *img_path = "/assets/img/";

extern void x_free(void *pointer);
extern void *x_malloc(unsigned long size);


extern char *assets_root_path() {
    if (root_path == NULL) {
        char tem[512];
        memset(tem, 0, 512);
        getcwd(tem, sizeof(tem));
        unsigned long len = strlen(tem);
        //预留一位结束位
        root_path = x_malloc(len + 1);
        memset(root_path, 0, len);
        for (int i = 0; i < len; ++i) {
            *(root_path + i) = tem[i];
        }
        *(root_path + len) = '\0';
    }
    return root_path;
}


extern GdkPixbuf *load_image(char *filename, GError *errs) {
    unsigned long len = strlen(img_path) + strlen(filename);
    char path[len];
    memset(path,0,len);
    strcat(path, img_path);
    strcat(path, filename);
    char *des = str_link(assets_root_path(), path);
    GdkPixbuf *pix_buf = gdk_pixbuf_new_from_file(des, &errs);
    if (errs != NULL) {
        printf("加载目标资源:[%s],发生错误:%s\n",filename,errs->message);
    }
    x_free(des);
    return pix_buf;
}

extern GdkPixbuf *load_image_none_err(char *filename) {
    return load_image(filename, NULL);
}



