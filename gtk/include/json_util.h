//
// Created by yangkui on 2021/7/10.
//

#ifndef X_LITE_JSON_UTIL_H
#define X_LITE_JSON_UTIL_H

#include "../include/cJSON.h"
/**
 * 从文件中加载json数据
 * @param filename  文件名
 * @return 返回json结构
 */
extern cJSON *parser_json_from_file(char *filename);

#endif //X_LITE_JSON_UTIL_H
