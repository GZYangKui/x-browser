//
// Created by yangkui on 2021/7/18.
//

#include "include/router.h"

/**
 * 可Popup和Pop路由
 */
typedef struct {
    Router *router;
    GtkWidget *widget;
    GtkWidget *headerBar;
} PopupAndPopRouter;


/**
 * 自定路由栈结构
 */
struct RouterStackFrame {
    struct RouterStackFrame *pre;
    struct RouterStackFrame *next;
    //路由缓存数据
    PopupAndPopRouter *router;
};

static GtkWindow *window = NULL;
/**
 * 栈顶
 */
static struct RouterStackFrame *top_stack = NULL;

extern void navigate_to(Router *router) {
    struct RouterStackFrame *frame = x_malloc(sizeof(struct RouterStackFrame));
    PopupAndPopRouter *pp_router = x_malloc(sizeof(PopupAndPopRouter));
    pp_router->router = router;
    pp_router->widget = router->widget();
    pp_router->headerBar = router->headerBar();

    frame->router = pp_router;

    frame->pre = NULL;
    frame->next = NULL;

    if (top_stack != NULL) {
        frame->pre = top_stack;
        top_stack->next = frame;
    }

    top_stack = frame;

    gtk_container_add(GTK_CONTAINER(window), frame->router->widget);
}


extern void redirect_to(Router router) {

}

extern void navigate_back(int delta) {

}

extern void navigate_window(GtkWindow *target) {
    if (window != NULL) {
        info("WINDOW 对象已经初始化,请勿重复初始化");
        return;
    }
    window = target;
}

