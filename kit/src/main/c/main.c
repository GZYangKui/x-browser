#include <stdio.h>
#include "util/util.h"

int main(int argc, char **argv) {
    int value = 60536;
    char *hex = to_hex(value);

    printf("%d转换为十六进制=%s\n",value,hex);

    int or_value = hex_to_natual(hex);

    printf("%s转换十进制=%d",hex,or_value);

    return 0;
}
