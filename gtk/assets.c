//
// Created by yangkui on 2021/7/6.
//

#include "assets.h"

char *root_path = NULL;

extern char *assets_root_path(){
    if (root_path == NULL){
        char tem[512];
        getcwd(tem,sizeof(tem));
        printf("实际路径:%s\n",tem);
        unsigned long len = strlen(tem);
        root_path = malloc(len);
        for (int i = 0; i < len; ++i) {
            *(root_path+i)=tem[i];
            printf("%s\n",root_path);
        }
        printf("路径初始化成功:%s\n",root_path);
    }
    return root_path;
}

void assets_load_error(GError **errs) {
    printf("捕获到异常信息:%s", "");
}

extern GdkPixbuf *load_image(char *filename, GError **errs) {
    GdkPixbuf *pix_buf = gdk_pixbuf_new_from_file(filename, errs);
    if (errs != NULL) {
        assets_load_error(errs);
    }
    return pix_buf;
}

extern GdkPixbuf *load_image_none_err(char *filename) {
    assets_root_path();
    return load_image(filename, NULL);
}



