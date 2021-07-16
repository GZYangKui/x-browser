//
// Created by yangkui on 2021/7/16.
//

#ifndef X_LITE_XD_OPERATE_H
#define X_LITE_XD_OPERATE_H

#include "common.h"
#include "sqlite3.h"
#include "assets.h"
#include "string_util.h"

/**
 *
 * 支出/收入分类
 *
 */
typedef struct {
    int16 id;
    int type;
    char *name;
    char *icon;
    int show;
    int16 createTime;
} FeeCategory;

/**
 * 使用宏释放FeeCategory对应内存
 */
#define FREE_FEE_CATEGORY(category) \
X_FREE((category)->name);              \
X_FREE((category)->icon);              \
X_FREE(category)


/**
 *
 * 检查数据库配置
 *
 */
extern int xd_check();


/**
 * 停止sqlite3相关实例
 */
extern void xd_stop();


/**
 * 获取支出分类列表
 */
extern GList *ex_cate();


#endif //X_LITE_XD_OPERATE_H
