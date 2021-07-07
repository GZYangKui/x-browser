//
// Created by yangkui on 2021/7/7.
//

#include "include/record_detail.h"

static GtkWidget *pane;

extern GtkWidget *det_widget() {
    pane = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(pane), gtk_label_new("测试"));
    return pane;
}

