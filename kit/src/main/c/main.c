#include <stdio.h>

int main(int argc, char **argv) {
    extern char *to_hex(int value);
    int value = 60536;
    char *hex = to_hex(value);

    printf("%d转换为十六进制=%s\n",value,hex);

    extern void c_brightness();

    c_brightness();

    return 0;
}
