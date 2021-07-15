#Cmake最低版本要求
cmake_minimum_required(VERSION 3.19)

#项目名称
project(x-lite VERSION 10)

if (CMAKE_HOST_WIN32)
    set(WIN 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

CONFIGURE_FILE(
        "${PROJECT_SOURCE_DIR}/env.in"
        "${PROJECT_SOURCE_DIR}/include/env.h"
)

find_package(PkgConfig REQUIRED)

find_package(Threads REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories("${GTK3_INCLUDE_DIRS}")

if (LINUX)
    set(EXT_LIBS "${PROJECT_SOURCE_DIR}/lib/linux")
elseif (WIN)
    MESSAGE(FATAL_ERROR "暂不支持WIN环境")
else ()
    MESSAGE(FATAL_ERROR "暂不支持MAC环境")
endif ()

add_subdirectory(util)

set(CMAKE_C_STANDARD 99)

FILE(COPY ./assets DESTINATION ${PROJECT_BINARY_DIR})

#遍历./下所有源文件 并且赋值给DIR_SRCS变量
aux_source_directory(. DIR_SRCS)
aux_source_directory(./include PROJECT_INCLUDE)

#指定生成目标
add_executable(Demo ${DIR_SRCS} ${PROJECT_INCLUDE})


target_include_directories(Demo PUBLIC "${PROJECT_BINARY_DIR}")

#添加链接库
link_directories(${EXT_LIBS})
target_link_libraries(Demo Util)
target_link_libraries(Demo /usr/lib/x86_64-linux-gnu/libm.so)
target_link_libraries(Demo ${GTK3_LIBRARIES} sqlite3 Threads::Threads)
