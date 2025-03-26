include_directories(../src/include)

add_executable(test test.cc)
target_link_libraries(test gcnetwork gchipe)


add_executable(client clienttest.cc)
add_executable(server servertest.cc)

add_executable(gchelp help.cpp)
add_executable(test_dst test_dst.cpp)
add_executable(test_coro test_coro.cpp)

add_executable(test_hipe test_hipe.cpp)
target_link_libraries(test_hipe gchipe)

add_executable(test_spdlog test_spdlog.cpp)
target_link_libraries(test_spdlog gcspdlog gchipe)

add_executable(test_buffer test_buffer.cpp)
add_executable(test_net test_net.cpp)
target_link_libraries(test_buffer gcnetwork)
target_link_libraries(test_net gcnetwork)