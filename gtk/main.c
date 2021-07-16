#include <gtk/gtk.h>
#include "include/x.h"
#include <pthread.h>
#include "include/sqlite3.h"
#include "include/x_lite.h"

/**
 * 初始化底部导航栏
 */
static NavigatorItem navigators[] = {
        {
                "明细",
                "/detail.png",
                NULL,
                HOME
        },
        {
                "图表",
                "/form.png",
                NULL,
                FORM
        },
        {
                "社区",
                "/fortune.png",
                NULL,
                FORTUNE
        },
        {
                "我的",
                "/my.png",
                NULL,
                PERSONAL
        }
};

string app_name = "鲨鱼记账";

static GtkWidget *window, *pane, *header, *center_box, *stack, *n_controller;

static void nav_action(GtkWidget *widget, NavigatorItem *item) {
    if (item->content == NULL) {
        return;
    }
    gtk_stack_set_visible_child((GtkStack *) stack, item->content);
    gtk_header_bar_set_subtitle((GtkHeaderBar *) header, item->title);
}

static GtkWidget *controller() {

    GtkWidget *btn_box;

    btn_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    int size = sizeof(navigators) / sizeof(NavigatorItem);

    for (int i = 0; i < size; ++i) {
        NavigatorItem *item = &navigators[i];

        GtkWidget *btn = gtk_button_new_with_label(item->title);
        gtk_container_add(GTK_CONTAINER(btn_box), btn);

        GtkWidget *content = NULL;
        switch (item->meta) {
            case HOME:
                content = det_widget();
                break;
            case FORM:
                content = form_widget();
                break;
            case FORTUNE:
                content = ft_widget();
                break;
            case PERSONAL:
                content = my_widget();
                break;
        }
        item->content = content;
        g_signal_connect(btn, "clicked", G_CALLBACK(nav_action), item);

        gtk_stack_add_named((GtkStack *) stack, content, item->title);
        //加载图片信息
        if (item->icon != NULL) {
            GdkPixbuf *buf = new_pix_buf_from_resource(item->icon);
            if (buf != NULL) {
                GtkWidget *icon = gtk_image_new_from_pixbuf(buf);
                gtk_button_set_image((GtkButton *) btn, icon);
                gtk_button_set_always_show_image((GtkButton *) btn, TRUE);
                gtk_button_set_image_position((GtkButton *) btn, GTK_POS_TOP);
                gtk_widget_show_all(btn);
            }
        }
    }

    return btn_box;
}

static void open_note_dialog(GtkWidget *widget, gpointer *data) {
    gtk_widget_hide(GTK_WIDGET(window));
    show_note_dialog();
    gtk_widget_show_all(GTK_WIDGET(window));
}

static void activate(GtkApplication *app, gpointer user_data) {

    //注册资源
    x_get_resource();

    //窗口相关设置
    stack = gtk_stack_new();
    n_controller = controller();
    header = gtk_header_bar_new();
    window = gtk_application_window_new(app);
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    pane = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    GtkWidget *note = gtk_button_new_with_label("记账");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), note);
    g_signal_connect(note, "clicked", G_CALLBACK(open_note_dialog), NULL);

    gtk_window_set_default_size(GTK_WINDOW (window), DEFAULT_WINDOW_WIDTH, DEFAULT_WIDOW_HEIGHT);

    gtk_widget_set_vexpand(GTK_WIDGET(stack), 1);
    gtk_header_bar_set_title((GtkHeaderBar *) header, app_name);
    gtk_header_bar_set_show_close_button((GtkHeaderBar *) header, TRUE);

    gtk_container_add(GTK_CONTAINER(center_box), stack);
    gtk_container_add(GTK_CONTAINER(center_box), n_controller);


    gtk_container_add(GTK_CONTAINER(pane), center_box);

    gtk_container_add(GTK_CONTAINER(window), pane);
    //自定义title bar
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GList *icons = new_pix_buf_list_from_resource(
            3,
            "/logo.png",
            "/logo@2x.png",
            "/logo@3x.png"
    );
    gtk_window_set_icon_list(GTK_WINDOW(window), icons);
    g_list_free(icons);

    gtk_widget_show_all(window);
}

int xd_check();
void xd_stop();

int main(int argc, char **argv) {
    if (xd_check()) {
        return 1;
    }
    GtkApplication *app;
    int status;
    app = gtk_application_new("cn.navigational.x-browser", G_APPLICATION_CAN_OVERRIDE_APP_ID);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    //stop sqlite3
    xd_stop();

    return status;
}
