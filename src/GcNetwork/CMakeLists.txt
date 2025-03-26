aux_source_directory(. SRC_LIST)

add_library(gcnetwork SHARED ${SRC_LIST})

link_libraries(gcnetwork gchipe)