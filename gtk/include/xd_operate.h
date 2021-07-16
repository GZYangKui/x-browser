//
// Created by yangkui on 2021/7/16.
//

#ifndef X_LITE_XD_OPERATE_H
#define X_LITE_XD_OPERATE_H

#include "common.h"
#include "sqlite3.h"
#include "assets.h"

/**
 *
 * 检查数据库配置
 *
 */
extern int xd_check();


/**
 * 停止sqlite3相关实例
 */
extern void xd_stop();

#endif //X_LITE_XD_OPERATE_H
