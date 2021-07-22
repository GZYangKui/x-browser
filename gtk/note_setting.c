//
// Created by yangkui on 2021/7/22.
//

#include "include/xd_operate.h"
#include "include/note_setting.h"

static GList *list;
static GtkWidget *box1;
static GtkWidget *box2;
static GtkWidget *stack;

static void init_item() {
    list = ex_cate();
    guint len = g_list_length(list);
    for (int i = 0; i < len; ++i) {
        GList *temp = g_list_nth(list, i);

        GtkWidget *btn = gtk_button_new();
        FeeCategory *cate = (FeeCategory *) temp->data;
        GtkWidget *label = gtk_label_new(cate->name);

        gtk_button_set_image(GTK_BUTTON(btn), gtk_image_new_from_resource("/remove@1x.png"));

        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

        gtk_container_add(GTK_CONTAINER(box), btn);
        if (cate->icon != NULL) {
            GtkWidget *img = gtk_image_new_from_resource(cate->icon);
            gtk_container_add(GTK_CONTAINER(box), img);
        }
        gtk_container_add(GTK_CONTAINER(box), label);

        if (cate->type == 0) {
            gtk_container_add(GTK_CONTAINER(box1), box);
        }
    }

    gtk_widget_show_all(box1);
    gtk_widget_show_all(box2);
}

static GtkWidget *header_bar() {
    GtkWidget *widget = gtk_header_bar_new();
    GtkWidget *switcher = gtk_stack_switcher_new();
    gtk_header_bar_set_custom_title(GTK_HEADER_BAR(widget), switcher);
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

    return widget;
}


static GtkWidget *main_pane() {
    GtkWidget *box, *btn, *scroll, *scroll1;
    stack = gtk_stack_new();
    box1 = gtk_list_box_new();
    box2 = gtk_list_box_new();
    btn = gtk_button_new_with_label("添加类别");
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    scroll1 = gtk_scrolled_window_new(NULL, NULL);

    gtk_button_set_always_show_image(GTK_BUTTON(btn), TRUE);
    gtk_button_set_image(GTK_BUTTON(btn), gtk_image_new_from_resource("/add@1x.png"));

    gtk_stack_add_titled(GTK_STACK(stack), scroll, "支出", "支出");
    gtk_stack_add_titled(GTK_STACK(stack), scroll1, "收入", "收入");

    gtk_widget_set_vexpand(stack, TRUE);

    gtk_container_add(GTK_CONTAINER(scroll), box1);
    gtk_container_add(GTK_CONTAINER(scroll1), box2);
    gtk_container_add(GTK_CONTAINER(box), stack);
    gtk_container_add(GTK_CONTAINER(box), btn);

    return box;
}

extern void *nav_note_setting() {
    Router *router;
    new_navigate_router(router, 0);


    router->title = "记账设置";
    router->widget = main_pane;
    router->headerBar = header_bar;

    navigate_to(router);

    init_item();
}



