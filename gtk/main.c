#include <gtk/gtk.h>
#include "include/x_lite.h"

/**
 * 初始化底部导航栏
 */
static struct NavigatorItem navigators[] = {
        {
                "明细",
                "detail.png"
        },
        {
                "图表",
                "form.png"
        },
        {
                "记账",
                "fee.png"
        },
        {
                "社区",
                "fortune.png"
        },
        {
                "我的",
                "my.png"
        }
};

static void navigator_action(GtkWidget *widget, struct NavigatorItem *item) {
    printf("%s被点击\n", item->title);
}

static GtkWidget *top_controller() {
    GtkWidget *btn_box;

    btn_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    int size = sizeof(navigators) / sizeof(navigators[0]);

    for (int i = 0; i < size; ++i) {
        struct NavigatorItem item = navigators[i];
        GtkWidget *btn = gtk_button_new_with_label(item.title);
        gtk_container_add(GTK_CONTAINER(btn_box), btn);
        //加载图片信息
        if (item.icon != NULL) {
            GdkPixbuf *buf = load_image_none_err(item.icon);
            if (buf == NULL){
                printf("加载导航图标:%s出错",item.icon);
                continue;
            }
            GtkWidget *icon = gtk_image_new_from_pixbuf(buf);
            gtk_button_set_image((GtkButton *) btn, icon);
            gtk_button_set_always_show_image((GtkButton *) btn,1);
            gtk_button_set_image_position((GtkButton *) btn, GTK_POS_TOP);
            gtk_widget_show_all(btn);
        }
        g_signal_connect(btn, "clicked", (GCallback) navigator_action, &item);
    }

    gtk_button_box_set_layout((GtkButtonBox *) btn_box, GTK_BUTTONBOX_EXPAND);


    return btn_box;
}

static GtkWidget *stack_switcher(GtkWidget *stack) {
    GtkWidget *switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack((GtkStackSwitcher *) switcher, (GtkStack *) stack);
    return switcher;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *pane, *window;

    GtkWidget *stack, *switcher;

    //窗口相关设置
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "x-browser");
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 600);
    gtk_window_set_icon(GTK_WINDOW(window), load_image_none_err("logo.png"));

    pane = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    stack = gtk_stack_new();
    switcher = stack_switcher(stack);

    gtk_stack_add_named((GtkStack *) stack, det_widget(), "det_widget");


    gtk_container_add(GTK_CONTAINER(pane), stack);
    gtk_container_add(GTK_CONTAINER(pane), top_controller());

    gtk_container_add(GTK_CONTAINER(window), pane);

    gtk_window_set_resizable(GTK_WINDOW(window), 0);
    gtk_widget_show_all(window);

}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("cn.navigational.x-browser", G_APPLICATION_CAN_OVERRIDE_APP_ID);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}