
aux_source_directory(. DIR_LIB_SRCS)


add_library(Util SHARED ${DIR_LIB_SRCS} ../common.c json_util.c ../include/json_util.h)

target_link_libraries(Util /usr/lib/x86_64-linux-gnu/libm.so)
