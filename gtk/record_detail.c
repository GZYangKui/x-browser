//
// Created by yangkui on 2021/7/7.
//

#include "include/record_detail.h"

static GtkWidget *pane;

static GtkWidget *override() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *box4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);


    GtkWidget *title = gtk_label_new("2021年");
    GtkWidget *btn = gtk_button_new_with_label("7月");
    gtk_button_set_image(
            (GtkButton *) btn,
            gtk_image_new_from_pixbuf(load_image_none_err("expand.png"))
    );
    gtk_container_add(GTK_CONTAINER(box1), title);
    gtk_container_add(GTK_CONTAINER(box1), btn);
    gtk_button_set_image_position((GtkButton *) btn, GTK_POS_RIGHT);
    gtk_button_set_always_show_image((GtkButton *) btn, 1);
    gtk_widget_set_halign(box1, GTK_ALIGN_CENTER);


    GtkWidget *title1 = gtk_label_new("收入");
    GtkWidget *title2 = gtk_label_new("支出");
    GtkWidget *title3 = gtk_label_new("0.00");
    GtkWidget *title4 = gtk_label_new("0.00");

    gtk_container_add(GTK_CONTAINER(box3), title1);
    gtk_container_add(GTK_CONTAINER(box3), title3);
    gtk_container_add(GTK_CONTAINER(box4), title2);
    gtk_container_add(GTK_CONTAINER(box4), title4);
    gtk_container_add(GTK_CONTAINER(box2), box3);
    gtk_container_add(GTK_CONTAINER(box2), box4);

    gtk_widget_set_hexpand(box3, 1);
    gtk_widget_set_hexpand(box4, 1);

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(box), box1);
    gtk_container_add(GTK_CONTAINER(box), separator);
    gtk_container_add(GTK_CONTAINER(box), box2);

    return box;
};

extern GtkWidget *det_widget() {
    pane = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *widget = gtk_tree_view_new();
    gtk_widget_set_vexpand(widget, 1);
    gtk_container_add(GTK_CONTAINER(pane), override());
    gtk_container_add(GTK_CONTAINER(pane), widget);
    return pane;
}

