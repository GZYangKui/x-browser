//
// Created by yangkui on 2021/7/7.
//

#ifndef X_LITE_X_LITE_H
#define X_LITE_X_LITE_H

#include "my.h"
#include "form.h"
#include "note.h"
#include "common.h"
#include "assets.h"
#include "fortune.h"
#include "record_detail.h"

typedef enum {
    HOME = 1,
    FORM,
    NOTE,
    FORTUNE,
    PERSONAL
} NavigatorItemMeta;
/**
 * 应用程序底部导航栏
 */
typedef struct {
    char *title;
    char *icon;
    GtkWidget *content;
    NavigatorItemMeta meta;
} NavigatorItem;

#endif //X_LITE_X_LITE_H
