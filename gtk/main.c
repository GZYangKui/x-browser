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
    int result = show_note_dialog();
    printf("%d\n", result);
    gtk_widget_show_all(GTK_WIDGET(window));
}


void *test(void *param) {
    printf("多线程\n");
    pthread_t _self = pthread_self();
    printf("%ld\n", _self);
    gtk_window_set_title(GTK_WINDOW(window), "测试");
    return NULL;
}

void bake_cake_thread(GTask *task,
                      gpointer source_object,
                      gpointer task_data,
                      GCancellable *cancellable) {
    printf("测试\n");
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

    gtk_window_set_title(GTK_WINDOW (window), app_name);
    gtk_window_set_default_size(GTK_WINDOW (window), DEFAULT_WINDOW_WIDTH, DEFAULT_WIDOW_HEIGHT);

    gtk_window_set_icon(GTK_WINDOW(window), new_pix_buf_from_resource("/logo.png"));


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

    gtk_widget_show_all(window);

    GTask *task = g_task_new(NULL, NULL, NULL, NULL);
    g_task_run_in_thread(task, bake_cake_thread);
    printf("%p\n", task);
}

sqlite3 *sqlite;

/**
 * 检查数据库文件是否存在
 *
 */
int check_db() {
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


int main(int argc, char **argv) {
//    if (check_db()) {
//        return 1;
//    }
//    GtkApplication *app;
//    int status;
//    app = gtk_application_new("cn.navigational.x-browser", G_APPLICATION_CAN_OVERRIDE_APP_ID);
//    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
//    status = g_application_run(G_APPLICATION (app), argc, argv);
//    g_object_unref(app);
//    sqlite3_close(sqlite);
//    return status;
}
