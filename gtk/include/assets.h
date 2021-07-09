//
// Created by yangkui on 2021/7/6.
//

#ifndef X_LITE_ASSETS_H
#define X_LITE_ASSETS_H

#include <gdk/gdk.h>

/**
 * 加载图片资源 不处理异常信息
 */
extern GdkPixbuf *load_image_none_err(char *filename);

/**
 * 加载图片资源
 *
 */
extern GdkPixbuf *load_image(char *filename, GError *errs);

/**
 * 获取资源根路径
 *
 */
extern char *assets_root_path();

#endif //X_LITE_ASSETS_H
