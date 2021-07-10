//
// Created by yangkui on 2021/7/9.
//
#include "include/fortune.h"
#include "include/json_util.h"
#include "include/assets.h"
#include "include/string_util.h"

GtkWidget *widget,*widget1;

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
            string name = cJSON_GetObjectItem(item,"name")->valuestring;
            gtk_flow_box_insert((GtkFlowBox *) widget, gtk_button_new_with_label(name),-1);
        }
    }
    X_FREE(json);
}

extern GtkWidget *note_widget() {
    widget = gtk_flow_box_new();
    widget1 = gtk_flow_box_new();
    init();
    return widget;
}
