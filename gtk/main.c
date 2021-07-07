#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *root_pane;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "x-browser");
    gtk_window_set_default_size(GTK_WINDOW (window), 600, 600);

    extern GdkPixbuf *load_image_none_err(char *filename);

    gtk_window_set_icon(GTK_WINDOW(window), load_image_none_err("logo.png"));

    root_pane = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window),root_pane);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);

    gtk_container_add(GTK_CONTAINER(root_pane),button);

    for (int i = 0; i <20 ; ++i) {
        gtk_container_add(GTK_CONTAINER(root_pane), gtk_label_new("test"));
    }

    gtk_notebook_set_tab_label((GtkNotebook *) root_pane, button, gtk_label_new("网页1"));
//    gtk_container_add(GTK_CONTAINER(root_pane), gtk_label_new("测试信息"));

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