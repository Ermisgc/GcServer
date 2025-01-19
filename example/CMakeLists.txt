include_directories(../src/include)
add_executable(test test.cpp)
add_executable(gchelp help.cpp)

target_link_libraries(test gcspdlog)
