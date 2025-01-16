include_directories(../src/include)
add_executable(test test.cpp)

target_link_libraries(test gcspdlog)
