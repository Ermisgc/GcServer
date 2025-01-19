include_directories(../include)

aux_source_directory(. SRC_LIST)

add_library(gcspdlog SHARED ${SRC_LIST})