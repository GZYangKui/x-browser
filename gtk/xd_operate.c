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

static int callback(void **list, int num, char **values, char **cols) {
    FeeCategory *category = x_malloc(sizeof(FeeCategory));

    category->id = atoi(*values);
    category->type = atoi(*(values + 1));
    category->name = str_malloc_cpy(*(values + 2));
    category->icon = str_malloc_cpy(*(values + 3));
    category->show = atoi(*(values + 4));
    category->createTime = atoi(*(values + 5));

    *list = g_list_append(*list, category);

    return 0;
}

extern GList *ex_cate() {
    char *sql = "SELECT * FROM category WHERE show=1";
    GList *list = NULL;
    char *err_msg = NULL;
    printf("%p\n", &list);
    sqlite3_exec(sqlite, sql, (int (*)(void *, int, char **, char **)) callback, &list, &err_msg);
    if (err_msg != NULL) {
        printf("执行sql出错:%s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return list;
}
