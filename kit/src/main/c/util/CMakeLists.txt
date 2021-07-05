
aux_source_directory(. DIR_LIB_SRCS)


add_library(Util SHARED ${DIR_LIB_SRCS})

add_executable(UtilDemo ${DIR_LIB_SRCS})

target_link_libraries(UtilDemo /usr/lib/x86_64-linux-gnu/libm.so)
