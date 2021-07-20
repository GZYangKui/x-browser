//
// Created by yangkui on 2021/7/20.
//

#include "include/ui_util.h"

static void trigger_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    gtk_dialog_response(dialog, response_id);
}

extern GtkWidget *new_confirm_dialog(const char *message) {
    GtkWidget *dialog = gtk_dialog_new();
    GtkWidget *area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "确认对话框");

    GtkWidget *label = gtk_label_new(message);
    GtkWidget *icon = gtk_image_new_from_resource("/dg_confirm.png");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40);

    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), icon);


    gtk_container_add(GTK_CONTAINER(area), box);

    gtk_widget_show_all(dialog);
    gint resp_id = TRUE;
    gint resp_id1 = FALSE;

    gtk_dialog_add_button(GTK_DIALOG(dialog), "确定", GTK_RESPONSE_OK);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "取消", GTK_RESPONSE_CANCEL);


    g_signal_connect (
            GTK_DIALOG(dialog),
            "response",
            G_CALLBACK(trigger_response),
            NULL
    );
    return dialog;
}

