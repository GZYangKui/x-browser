//
// Created by yangkui on 2021/7/9.
//
#include "include/note.h"
#include "include/json_util.h"
#include "include/assets.h"
#include "include/sqlite3.h"
#include "include/string_util.h"
#include "include/xd_operate.h"

#define ZERO "0.00"

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

GtkWidget *scroll;
GtkWidget *scroll1;

static GtkWidget *box = NULL;
static GtkWidget *dialog = NULL;
static gboolean show_kw = FALSE;
static GtkWidget *inner_box = NULL;


static void calculate() {
    const char *text = gtk_label_get_label(GTK_LABEL(money));
    int index = -1;
    //运算规则 1(+) -1(-)
    int opera = 1;
    int16 len = strlen(text);
    for (int i = 0; i < len; ++i) {
        char temp = *(text + i);
        if (temp == '+' || temp == '-') {
            index = i;
            opera = (temp == '+') ? 1 : -1;
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
    char a[index + 1];
    char b[len];

    memset(a, 0, index + 1);
    memset(b, 0, len);

    strncpy(a, text, index);
    strncpy(b, (text + index + 1), len);

    double af = atof(a);
    double bf = atof(b);

    double total;
    if (opera == 1) {
        total = af + bf;
    } else {
        total = af - bf;
    }

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
    return strcmp(str, "+") == 0 || strcmp(str, "-") == 0;
}

static gboolean has_opera(const char *text) {
    int16 len = strlen(text);
    gboolean rs = FALSE;
    for (int i = len - 1; i >= 0; --i) {
        char k = *(text + i);
        if (k == '+' || k == '-') {
            rs = TRUE;
            break;
        }
    }
    return rs;
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
        if (is_opera(data)) {
            return;
        }
        strcat(new_text, data);
    } else {
        strcat(new_text, text);
    }
    //判断是否可以添加操作符号(+/-)
    if (is_opera(data) && !zero) {
        if (has_opera(text)) {
            calculate();
            return;
        }
        strcat(new_text, data);

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

static GtkWidget *get_keyword() {
    GtkWidget *grid = gtk_grid_new();
    for (int i = 0; i < 16; ++i) {
        int row = i / 4;
        int column = i % 4;
        const char *name = keywords[i];
        GtkWidget *btn = gtk_button_new_with_label(name);
        if (strcmp(name, "x") == 0) {
            btn = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(btn),
                                 gtk_image_new_from_pixbuf(new_pix_buf_from_resource("/kw_clear.png")));
            gtk_button_set_always_show_image(GTK_BUTTON(btn), TRUE);
        }
        gtk_widget_set_hexpand(btn, TRUE);
        gtk_grid_attach(GTK_GRID(grid), btn, column, row, 1, 1);
        g_signal_connect(btn, "clicked", G_CALLBACK(k_clicked), name);
    }
    return grid;
}

static GtkWidget *get_inner_box() {
    money = gtk_label_new(ZERO);
    GtkWidget *_inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new("备注");
    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "点击输入备注");
    gtk_container_add(GTK_CONTAINER(box1), label);
    gtk_container_add(GTK_CONTAINER(box1), entry);
    gtk_container_add(GTK_CONTAINER(box1), money);

    GtkWidget *keyword = get_keyword();
    gtk_widget_set_hexpand(keyword, TRUE);
    gtk_container_add(GTK_CONTAINER(_inner_box), box1);
    gtk_container_add(GTK_CONTAINER(_inner_box), keyword);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/kw_style.css");
    gtk_style_context_add_provider(
            gtk_widget_get_style_context(_inner_box),
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_FALLBACK
    );

    return _inner_box;
}

static void item_select(GtkWidget *btn, FeeCategory *item) {
    printf("name:%s\n", item->name);
    if (show_kw == TRUE) {
        return;
    }
    gtk_container_remove(GTK_CONTAINER(box), inner_box);
    gtk_container_add(GTK_CONTAINER(box), inner_box);
    gtk_widget_show_all(box);
    show_kw = TRUE;
}


static void update_item(FeeCategory *item, gpointer user_data) {
    GtkWidget *btn = gtk_button_new_with_label(item->name);
    GtkWidget *image = gtk_image_new_from_pixbuf(new_pix_buf_from_resource(item->icon));
    gtk_button_set_image(GTK_BUTTON(btn), image);
    gtk_button_set_image_position(GTK_BUTTON(btn), GTK_POS_TOP);
    gtk_button_set_always_show_image(GTK_BUTTON(btn), TRUE);
    if (item->type == 0) {
        gtk_container_add(GTK_CONTAINER(widget), btn);
    } else {
        gtk_container_add(GTK_CONTAINER(widget1), btn);
    }
    g_signal_connect(btn, "clicked", G_CALLBACK(item_select), item);
}

static void switcher_changed(GtkWidget *switcher, gpointer *user_data) {
    if (show_kw == FALSE) {
        return;
    }
    g_object_ref(inner_box);
    gtk_container_remove(GTK_CONTAINER(box), inner_box);
    show_kw = FALSE;
}

static GList *list = NULL;

extern GtkWidget *note_widget() {

    GtkWidget *_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    stack = gtk_stack_new();
    inner_box = get_inner_box();
    widget = gtk_flow_box_new();
    widget1 = gtk_flow_box_new();
    controller = gtk_stack_switcher_new();
    scroll = gtk_scrolled_window_new(NULL, NULL);
    scroll1 = gtk_scrolled_window_new(NULL, NULL);

    gtk_widget_set_valign(widget, GTK_ALIGN_START);
    gtk_widget_set_halign(widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(widget1, GTK_ALIGN_START);
    gtk_widget_set_halign(widget1, GTK_ALIGN_FILL);

    gtk_container_add(GTK_CONTAINER(scroll), widget);
    gtk_container_add(GTK_CONTAINER(scroll1), widget1);

    gtk_stack_add_titled(GTK_STACK(stack), scroll, "收入", "支出");
    gtk_stack_add_titled(GTK_STACK(stack), scroll1, "支出", "收入");


    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(controller), GTK_STACK(stack));
    g_signal_connect(stack, "notify::visible-child", G_CALLBACK(switcher_changed), NULL);


    gtk_container_add(GTK_CONTAINER(_box), stack);
    gtk_widget_set_vexpand(GTK_WIDGET(stack), TRUE);

    gtk_widget_set_halign(controller, GTK_ALIGN_CENTER);


    list = ex_cate();
    g_list_foreach(list, (GFunc) update_item, NULL);

    return _box;
}


static void open_setting(GtkWidget *setting,gpointer *user_data){
//    GtkWidget *window = gtk_dialog_new();

   // gtk_widget_set_visible(dialog,FALSE);

//    gtk_widget_show_all(window);
//    gtk_dialog_run(GTK_DIALOG(window));
//
//    gtk_widget_set_visible(dialog,TRUE);
}

static void dispose(){
    if (list==NULL){
        return;
    }
    int16 len = g_list_length(list);
    for (int i = 0; i <len ; ++i) {
        FeeCategory *category = g_list_nth_data(list,i);
        FREE_FEE_CATEGORY(category);
    }
    g_list_free(list);
    list = NULL;
}

extern int show_note_dialog() {
    show_kw = FALSE;
    box = note_widget();
    dialog = gtk_dialog_new();
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), box);

    GtkWidget *header_bar = gtk_header_bar_new();
    GtkWidget *setting = gtk_button_new_with_label("设置");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_custom_title(GTK_HEADER_BAR(header_bar), controller);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), setting);
    g_signal_connect(setting,"clicked",G_CALLBACK(open_setting),NULL);

    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_titlebar(GTK_WINDOW(dialog), header_bar);
    gtk_window_set_default_size(GTK_WINDOW(dialog), DEFAULT_WINDOW_WIDTH, DEFAULT_WIDOW_HEIGHT);
    gtk_widget_show_all(dialog);
    int result = gtk_dialog_run(GTK_DIALOG(dialog));
    dispose();
    gtk_widget_destroy(dialog);
    return result;
}
