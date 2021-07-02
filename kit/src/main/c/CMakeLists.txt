#Cmake最低版本要求
cmake_minimum_required(VERSION 3.19)

#项目名称
project(x-lite)

set(CMAKE_C_STANDARD 99)


add_subdirectory(util)
add_subdirectory(screen)

#遍历./下所有源文件 并且赋值给DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo ${DIR_SRCS})

#添加链接库
target_link_libraries(Demo Util)
target_link_libraries(Demo Screen)
target_link_libraries(Demo /usr/lib/x86_64-linux-gnu/libm.so)