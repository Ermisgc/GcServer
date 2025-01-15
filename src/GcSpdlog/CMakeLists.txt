include_directories(../include/GcSpdlog)

aux_source_directory(. SRC_LIST)

add_library(gcspdlog SHARED ${SRC_LIST})