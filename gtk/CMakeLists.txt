#Cmake最低版本要求
cmake_minimum_required(VERSION 3.19)

#项目名称
project(x-lite VERSION 10)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories("${GTK3_INCLUDE_DIRS}")
list(APPEND GTK_LIBS ${GTK3_LIBRARIES})


add_subdirectory(util)
add_subdirectory(macro)

set(CMAKE_C_STANDARD 99)

FILE(COPY ./assets DESTINATION ${PROJECT_BINARY_DIR})

#遍历./下所有源文件 并且赋值给DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo ${DIR_SRCS})

#添加链接库
target_link_libraries(Demo Util)
target_link_libraries(Demo ${GTK_LIBS})
target_link_libraries(Demo /usr/lib/x86_64-linux-gnu/libm.so)
target_include_directories(Demo PUBLIC "${PROJECT_BINARY_DIR}")
