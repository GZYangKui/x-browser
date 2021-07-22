//
// Created by yangkui on 2021/7/20.
//

#include "include/ui_util.h"

extern GtkWidget *new_confirm_dialog(const GtkWindow *window, const char *message) {
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
            "确认对话框",
            GTK_WINDOW(window),
            flags,
            "确定",
            GTK_RESPONSE_OK,
            "取消",
            GTK_RESPONSE_CANCEL,
            NULL
    );
    GtkWidget *area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    GtkWidget *label = gtk_label_new(message);
    GtkWidget *icon = gtk_image_new_from_resource("/dg_confirm.png");

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40);

    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), icon);


    gtk_container_add(GTK_CONTAINER(area), box);

    gtk_widget_show_all(dialog);

    return dialog;
}

