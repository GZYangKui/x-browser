#include <gtk/gtk.h>
#include "include/x_lite.h"

/**
 * 初始化底部导航栏
 */
static NavigatorItem navigators[] = {
        {
                "明细",
                "detail.png",
                HOME
        },
        {
                "图表",
                "form.png",
                FORM
        },
        {
                "记账",
                "fee.png",
                NOTE
        },
        {
                "社区",
                "fortune.png",
                FORTUNE
        },
        {
                "我的",
                "my.png",
                PERSONAL
        }
};

const char *app_name = "鲨鱼记账";

static GtkWidget *window, *header, *switcher;

static void navigator_action(GtkWidget *widget, NavigatorItem *item) {
    printf("%s被点击\n",item->title);
}

static GtkWidget *controller(GtkWidget *stack) {
    GtkWidget *btn_box;

    btn_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    int size = sizeof(navigators) / sizeof(navigators[0]);

    for (int i = 0; i < size; ++i) {
        NavigatorItem *item = &navigators[i];

        GtkWidget *btn = gtk_button_new_with_label(item->title);
        gtk_container_add(GTK_CONTAINER(btn_box), btn);


        g_signal_connect(btn, "clicked", G_CALLBACK(navigator_action), item);

        if (item->meta == HOME) {
            gtk_stack_add_named((GtkStack *) stack, det_widget(), "det_widget");
        }

        //加载图片信息
        if (item->icon != NULL) {
            GdkPixbuf *buf = load_image_none_err(item->icon);
            if (buf != NULL) {
                printf("加载图标:%s\n", item->icon);
                GtkWidget *icon = gtk_image_new_from_pixbuf(buf);
                gtk_button_set_image((GtkButton *) btn, icon);
                gtk_button_set_always_show_image((GtkButton *) btn, 1);
                gtk_button_set_image_position((GtkButton *) btn, GTK_POS_TOP);
                gtk_widget_show_all(btn);
                printf("完成加载:%s\n", item->icon);
            }
        }
    }

    return btn_box;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *stack, *pane, *center_box;

    //窗口相关设置
    stack = gtk_stack_new();
    header = gtk_header_bar_new();
    window = gtk_application_window_new(app);
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    pane = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    gtk_window_set_title(GTK_WINDOW (window), app_name);
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 600);
    gtk_window_set_icon(GTK_WINDOW(window), load_image_none_err("logo.png"));


    gtk_widget_set_vexpand(GTK_WIDGET(stack), 1);
    gtk_header_bar_set_title((GtkHeaderBar *) header, app_name);
    gtk_header_bar_set_show_close_button((GtkHeaderBar *) header, 1);

    switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack((GtkStackSwitcher *) switcher, (GtkStack *) stack);

    gtk_stack_switcher_set_stack((GtkStackSwitcher *) switcher, (GtkStack *) stack);


    gtk_container_add(GTK_CONTAINER(center_box), stack);
    gtk_container_add(GTK_CONTAINER(center_box), controller(stack));


    gtk_container_add(GTK_CONTAINER(pane), header);
    gtk_container_add(GTK_CONTAINER(pane), center_box);

    gtk_container_add(GTK_CONTAINER(window), pane);

    gtk_window_set_resizable(GTK_WINDOW(window), 0);
    gtk_window_set_decorated(GTK_WINDOW(window), 0);
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
