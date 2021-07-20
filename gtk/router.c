//
// Created by yangkui on 2021/7/18.
//

#include "include/router.h"
#include "include/assets.h"
#include "include/ui_util.h"

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
struct _RouterStackFrame {
    struct _RouterStackFrame *pre;
    struct _RouterStackFrame *next;
    //路由缓存数据
    PopupAndPopRouter *router;
};

typedef struct _RouterStackFrame RouterStackFrame;


static GtkWidget *box = NULL;
static GtkWindow *window = NULL;
static GtkWidget *navigate_bar = NULL;
/**
 * 栈顶
 */
static RouterStackFrame *top_stack = NULL;

static void free_router_stack_frame(RouterStackFrame *frame) {
    PopupAndPopRouter *_router = frame->router;
    gtk_widget_destroy(_router->widget);
    gtk_widget_destroy(_router->headerBar);
    X_FREE(_router->router);
    frame = frame->pre;
}

static void update_window_page(PopupAndPopRouter *router) {
    //如果存在自定义title_bar则使用自定义title_bar
    if (router->headerBar != NULL) {
        gtk_window_set_titlebar(window, router->headerBar);
    }
    gtk_container_add(GTK_CONTAINER(box), router->widget);
    gtk_widget_show_all(GTK_WIDGET(window));
}

extern void navigate_to(Router *router) {
    RouterStackFrame *frame = x_malloc(sizeof(RouterStackFrame));
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
        //引用+1
        g_object_ref(top_stack->router->widget);
        if (top_stack->router->headerBar != NULL) {
            g_object_ref(top_stack->router->headerBar);
        }
        gtk_container_remove(GTK_CONTAINER(box), top_stack->router->widget);
    }

    top_stack = frame;

    update_window_page(pp_router);

}


extern void redirect_to(Router *router) {
    RouterStackFrame *frame = top_stack;
    do {
        PopupAndPopRouter *_router = frame->router;
        gtk_widget_destroy(_router->widget);
        gtk_widget_destroy(_router->headerBar);
        X_FREE(_router->router);
        frame = frame->pre;
    } while (frame != NULL);
    //重定向页面
    navigate_to(router);
}

extern void navigate_back(int delta) {
    int index = 0;
    RouterStackFrame *frame = top_stack;
    while (index < delta && frame->pre != NULL) {
        ++index;
        RouterStackFrame *temp = frame;
        frame = frame->pre;
        frame->next = NULL;
        free_router_stack_frame(temp);
    }
    top_stack = frame;
    update_window_page(frame->router);
}

/**
 * 返回上一个路由,如果上一个路由为空,则弹出对话框询问用户是否退出当前程序
 */
static void left_action(GtkWidget *widget, gpointer user_data) {
    if (top_stack->pre == NULL) {
        //显示确定退出程序对话框
        GtkWidget *dialog = new_confirm_dialog("确定要退出当前程序?");

        gint rs = gtk_dialog_run(GTK_DIALOG(dialog));

        printf("响应结果:%d\n",rs);
        return;
    }
    navigate_back(1);
}

static GtkWidget *b_navigate_bar() {
    gint width;
    gint height;
    gtk_window_get_size(window, &width, &height);
    gint spacing = width / 6;
    GtkWidget *_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, spacing);

    gtk_widget_set_halign(_box, GTK_ALIGN_CENTER);

    GtkWidget *left = gtk_button_new();
    GtkWidget *center = gtk_button_new();
    GtkWidget *right = gtk_button_new();


    gtk_button_set_image(
            GTK_BUTTON(left),
            gtk_image_new_from_resource("/nav_back.png")
    );
    gtk_button_set_image(
            GTK_BUTTON(center),
            gtk_image_new_from_resource("/nav_home.png")
    );
    gtk_button_set_image(
            GTK_BUTTON(right),
            gtk_image_new_from_resource("/nav_func.png")
    );

    g_signal_connect(left, "clicked", G_CALLBACK(left_action), NULL);

    register_css_context(_box, "nav_style.css", 1);

    gtk_container_add(GTK_CONTAINER(_box), left);
    gtk_container_add(GTK_CONTAINER(_box), center);
    gtk_container_add(GTK_CONTAINER(_box), right);

    return _box;
}

extern void navigate_window(GtkWindow *target, gboolean show_nav_bar) {
    if (window != NULL) {
        info("WINDOW 对象已经初始化,请勿重复初始化");
        return;
    }
    window = target;
    navigate_bar = b_navigate_bar();
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(_box), box);
    if (show_nav_bar) {
        gtk_container_add(GTK_CONTAINER(_box), navigate_bar);
    }
    gtk_container_add(GTK_CONTAINER(window), _box);
}

