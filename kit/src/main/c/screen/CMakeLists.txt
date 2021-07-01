# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

#生成链接库
add_library(Screen SHARED ${DIR_LIB_SRCS})

set(XRANDR /usr/lib/x86_64-linux-gnu/libXrandr.so)

find_package(X11)

if (X11_FOUND)
    MESSAGE("${X11_LIBRARY}")
    target_link_libraries(Screen ${X11_LIBRARIES})
    target_link_libraries(Screen ${XRANDR})

endif ()

target_link_libraries(Screen /usr/local/lib/libglfw3.a)