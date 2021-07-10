//
// Created by yangkui on 2021/7/10.
//

#include "../include/common.h"
#include "../include/json_util.h"
#include "../include/file_util.h"

extern cJSON *parser_json_from_file(char *filename) {
    string json_str = r_file(filename);
    if (json_str == NULL){
        return NULL;
    }
    return cJSON_Parse(json_str);
}
