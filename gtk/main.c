#include <gtk/gtk.h>
#include "include/record_detail.h"

static GtkWidget *top_controller() {
    GtkWidget *btn_box, *btn, *btn1, *btn2, *btn3, *btn4;
    btn = gtk_button_new_with_label("明细");
    btn1 = gtk_button_new_with_label("图表");
    btn2 = gtk_button_new_with_label("记账");
    btn3 = gtk_button_new_with_label("社区");
    btn4 = gtk_button_new_with_label("我的");

    btn_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(btn_box), btn);
    gtk_container_add(GTK_CONTAINER(btn_box), btn1);
    gtk_container_add(GTK_CONTAINER(btn_box), btn2);
    gtk_container_add(GTK_CONTAINER(btn_box), btn3);
    gtk_container_add(GTK_CONTAINER(btn_box), btn4);

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
    gtk_window_set_default_size(GTK_WINDOW (window), 600, 600);
    gtk_window_set_icon(GTK_WINDOW(window), load_image_none_err("logo.png"));

    pane = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    stack = gtk_stack_new();
    switcher = stack_switcher(stack);

    gtk_stack_add_named((GtkStack *) stack, det_widget(), "det_widget");


    gtk_container_add(GTK_CONTAINER(pane), stack);
    gtk_container_add(GTK_CONTAINER(pane), top_controller());

    gtk_container_add(GTK_CONTAINER(window), pane);

    gtk_window_set_resizable(GTK_WINDOW(window),0);
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