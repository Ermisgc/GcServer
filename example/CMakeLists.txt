include_directories(../src/include)

add_executable(test test.cc)
add_executable(client clienttest.cc)
add_executable(server servertest.cc)

add_executable(gchelp help.cpp)
# add_executable(test_rbtree test_rbtree.cpp)

add_executable(test_hipe test_hipe.cpp)
target_link_libraries(test_hipe gchipe)

add_executable(test_spdlog test_spdlog.cpp)
target_link_libraries(test_spdlog gcspdlog gchipe)