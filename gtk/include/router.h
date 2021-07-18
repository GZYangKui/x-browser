//
// Created by yangkui on 2021/7/18.
//

#ifndef X_LITE_ROUTER_H
#define X_LITE_ROUTER_H

#include <gtk/gtk.h>
#include "common.h"

typedef struct _Router Router;

typedef GtkWidget *(*RouterWidget)(void);

/**
 * 入栈成功回调
 */
typedef void (*OnSuccess)(Router router);


/**
 * 入栈失败回调
 */
typedef void (*OnFailed)(Router router, GError *error);

/**
 * 路由参数
 */
typedef struct {
    char *key;
    char *value;
} RouterParam;

struct _Router {
    //路由路径
    char *path;
    //路由名称
    char *title;
    //入栈成功回调
    OnFailed onSuccess;
    //入栈失败回调
    OnSuccess onFailed;
    //路由对应的页面信息
    RouterWidget widget;
    //当前页面对饮状态栏
    RouterWidget headerBar;
    //路由参数
    RouterParam params[];
};


/**
 * 自定义宏用于生成包含指定数量参数Router对象
 */
#define new_navigate_router(len) (Router *)x_malloc(sizeof(Router)+((len)*sizeof(RouterParam)))

/**
 *
 * 导航到某个页面
 *
 */
extern void navigate_to(Router *router);

/**
 * 重定向到某个页面并清除之前页面
 */
extern void redirect_to(Router router);

/**
 *
 * 从当前路由返回上级路由，返回几级由{@param delta}确定
 *
 */
extern void navigate_back(int delta);

/**
 *
 * 初始化最外层窗口对象
 *
 */
extern void navigate_window(GtkWindow *widow);

#endif //X_LITE_ROUTER_H
