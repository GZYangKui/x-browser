//
// Created by yangkui on 2021/7/6.
//

#ifndef X_LITE_ASSETS_H
#define X_LITE_ASSETS_H

#include "common.h"
#include <gdk/gdk.h>

/**
 * 获取资源根路径
 *
 */
extern int16 project_path(char *buf, int size);

/**
 *
 * 获取资源文件
 *
 */
extern GdkPixbuf *new_pix_buf_from_resource(char *id);

/**
 * 加载资源列表
 */
extern GList *new_pix_buf_list_from_resource(int size, ...);

/**
 * 注册css context到指定GtkWidget上
 */
extern GtkCssProvider *register_css_context(GtkWidget *widget,char *filename,gint prior);


#endif //X_LITE_ASSETS_H
