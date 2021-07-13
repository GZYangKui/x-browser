//
// Created by yangkui on 2021/7/9.
//
#include "include/note.h"
#include "include/json_util.h"
#include "include/assets.h"
#include "include/string_util.h"

#define ZERO "0.00"

static GtkWidget *box;
static GtkWidget *widget;
static GtkWidget *widget1;
static GtkWidget *stack;
static GtkWidget *money;
static GtkWidget *controller;
static GtkWidget *inner_box;

static const char *keywords[] = {
        "7",
        "8",
        "9",
        "d",
        "4",
        "5",
        "6",
        "+",
        "1",
        "2",
        "3",
        "-",
        ".",
        "0",
        "x",
        "完成"
};

static void calculate() {
    const char *text = gtk_label_get_label(GTK_LABEL(money));
    int index = -1;
    int16 len = strlen(text);
    for (int i = 0; i < len; ++i) {
        char temp = *(text + i);
        if (temp == '+' || temp == '-') {
            index = i;
            break;
        }
    }
    //未找到运算符(+/-)
    if (index == -1) {
        return;
    }
    //不满足两位运算
    if (index == len - 1) {
        return;
    }
    char a[index];
    char b[len - index];

    memset(a, 0, index);
    memset(b, 0, len - index);

    strncpy(a, text, index);
    strncpy(b, text + index, len - index);

    double af = atof(a);
    double bf = atof(b);

    printf("%lf\n", af);
    printf("%lf\n", bf);

    double total = af + bf;

    char t[64];

    sprintf(t, "%.2f", total);

    gtk_label_set_label(GTK_LABEL(money), t);
}

static gboolean is_ct(f_string str) {
    gboolean rs = strcmp(str, "d") == 0 || strcmp(str, "x") == 0 || strcmp(str, "完成") == 0;

    //清除输入数据
    if (strcmp(str, "x") == 0) {
        gtk_label_set_label((GtkLabel *) money, ZERO);
    }

    //计算结果
    if (strcmp(str, "完成") == 0) {
        calculate();
    }
    //触发日期选择
    if (strcmp(str, "d") == 0) {

    }
    return rs;
}

/**
 * 判断是否运算符
 */
static gboolean is_opera(const char *str) {
    return *str == '+' || *str == '-';
}

static gboolean has_opera(const char *text) {
    int16 len = strlen(text);
    if (len == 0) {
        return FALSE;
    }
    const char *c = text + len - 1;
    return is_opera(c);
}

static gboolean can_add_dot() {
    const char *text = gtk_label_get_label((GtkLabel *) money);
    int16 len = strlen(text);
    gboolean rs = TRUE;
    for (int16 i = len - 1; i >= 0; --i) {
        const char p = *(text + i);
        if (p == '+' || p == '-' || p == '.') {
            if (p == '.') {
                rs = FALSE;
            }
            break;
        }
    }
    return rs;
}

static void k_clicked(GtkWidget *btn, const char *data) {
    if (is_ct(data)) {
        return;
    }
    //判断是否控制键
    const char *text = gtk_label_get_label((GtkLabel *) money);
    int16 len = strlen(text) + 2;
    char new_text[len];
    memset(new_text, 0, len);
    gboolean zero = strcmp(ZERO, text) == 0;
    //如果当前数字为0=>直接拷贝
    if (zero) {
        strcat(new_text, data);
    } else {
        strcat(new_text, text);
    }
    //判断是否可以添加操作符号(+/-)
    if (is_opera(data) && !zero) {
        if (!has_opera(text)) {
            strcat(new_text, data);
        } else {
            calculate();
        }
    } else {
        if (!zero) {
            gboolean rs = TRUE;
            if (strcmp(data, ".") == 0) {
                rs = can_add_dot();
            }
            if (rs) {
                strcat(new_text, data);
            }
        }
    }
    gtk_label_set_label(GTK_LABEL(money), new_text);
}

static GtkWidget *keyword() {

    GtkWidget *grid = gtk_grid_new();
    for (int i = 0; i < 16; ++i) {
        int row = i / 4;
        int column = i % 4;
        const char *name = keywords[i];
        GtkWidget *btn = gtk_button_new_with_label(name);
        if (strcmp(name, "x") == 0) {
            btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(btn), gtk_image_new_from_resource("clear.png"));
            gtk_button_set_always_show_image(GTK_BUTTON(btn), TRUE);
        }
        gtk_widget_set_hexpand(btn, TRUE);
        gtk_grid_attach(GTK_GRID(grid), btn, column, row, 1, 1);
        g_signal_connect(btn, "clicked", G_CALLBACK(k_clicked), name);
    }
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "kw_style.css");
    gtk_style_context_add_provider(
            gtk_widget_get_style_context(grid),
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_FALLBACK
    );

    return grid;
}

static GtkWidget *get_inner_box() {
    money = gtk_label_new(ZERO);
    inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new("备注");
    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "点击输入备注");
    gtk_container_add(GTK_CONTAINER(box1), label);
    gtk_container_add(GTK_CONTAINER(box1), entry);
    gtk_container_add(GTK_CONTAINER(box1), money);

    GtkWidget *grid = keyword();
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_container_add(GTK_CONTAINER(inner_box), box1);
    gtk_container_add(GTK_CONTAINER(inner_box), grid);

    GdkRGBA color;
    color.alpha = 1;
    color.red = .38;
    color.blue = .38;
    color.green = .38;
//    gtk_widget_override_background_color(GTK_WIDGET(inner_box), GTK_STATE_FLAG_NORMAL, &color);

    GtkCssProvider *provider = gtk_css_provider_new();

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
    GtkWidget *scroll;
    GtkWidget *scroll1;

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
