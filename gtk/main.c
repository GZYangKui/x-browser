#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "x-browser");
    gtk_window_set_default_size(GTK_WINDOW (window), 600, 600);

    extern GdkPixbuf *load_image_none_err(char *filename);

    gtk_window_set_icon(GTK_WINDOW(window), load_image_none_err("logo.png"));

     button_box = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(window),button_box);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK(print_hello), NULL);

    gtk_container_add(GTK_CONTAINER(button_box),button);

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