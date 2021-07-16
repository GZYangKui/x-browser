//
// Created by yangkui on 2021/7/16.
//
#include "include/xd_operate.h"

static sqlite3 *sqlite = NULL;

extern int xd_check() {
    char path[512];
    memset(path, 0, 512);
    int16 len = project_path(path, 512);
    strncat(path, "/data/xb.db", 512 - len);
    int rs = sqlite3_open(path, &sqlite);
    if (rs) {
        fprintf(stderr, "无法打开数据库文件:%s", sqlite3_errmsg(sqlite));
        sqlite3_close(sqlite);
    }
    return rs;
}

extern void xd_stop() {
    if (sqlite == NULL) {
        return;
    }
    sqlite3_close(sqlite);
}
