//
// Created by yangkui on 2021/7/9.
//
#include "include/note.h"
#include "include/json_util.h"
#include "include/assets.h"
#include "include/string_util.h"

static GtkWidget *box;
static GtkWidget *widget;
static GtkWidget *widget1;
static GtkWidget *stack;
static GtkWidget *controller;
static GtkWidget *inner_box;

static GtkWidget *get_inner_box() {
    inner_box = gtk_grid_new();

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new("备注");
    GtkWidget *money = gtk_label_new("0.00");
    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "点击输入备注");
    gtk_container_add(GTK_CONTAINER(box1), label);
    gtk_container_add(GTK_CONTAINER(box1), entry);
    gtk_container_add(GTK_CONTAINER(box1), money);

    gtk_grid_attach(GTK_GRID(inner_box), box1, 0, 0, 4, 1);

    return inner_box;
}

static void item_select(GtkWidget *btn, NoteItem *item) {
    printf("name:%s\n", item->name);
}


static void init() {
    string root = assets_root_path();
    string target = str_link(root, "/assets/config/disburse.json");
    cJSON *json = parser_json_from_file(target);
    X_FREE(target);
    if (json != NULL) {
        cJSON *arr = cJSON_GetObjectItem(json, "disburse");
        int size = cJSON_GetArraySize(arr);
        for (int i = 0; i < size; ++i) {
            cJSON *item = cJSON_GetArrayItem(arr, i);
            NoteItem *n_item = x_malloc(sizeof(NoteItem));
            n_item->name = cJSON_GetObjectItem(item, "name")->valuestring;
            GtkWidget *btn = gtk_button_new_with_label(n_item->name);
            gtk_flow_box_insert((GtkFlowBox *) widget, btn, -1);
            g_signal_connect(btn, "clicked", G_CALLBACK(item_select), n_item);
        }
    }
    X_FREE(json);
}

extern GtkWidget *note_widget() {
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    stack = gtk_stack_new();
    widget = gtk_flow_box_new();
    widget1 = gtk_flow_box_new();
    controller = gtk_stack_switcher_new();

    gtk_stack_add_titled(GTK_STACK(stack), widget, "收入", "支出");
    gtk_stack_add_titled(GTK_STACK(stack), widget1, "支出", "收入");


    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(controller), GTK_STACK(stack));

    gtk_container_add(GTK_CONTAINER(box), controller);
    gtk_container_add(GTK_CONTAINER(box), stack);
    gtk_container_add(GTK_CONTAINER(box), get_inner_box());
    gtk_widget_set_vexpand(GTK_WIDGET(stack), TRUE);

    gtk_widget_set_halign(controller, GTK_ALIGN_CENTER);

    init();
    return box;
}
