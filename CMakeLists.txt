cmake_minimum_required (VERSION 3.11)

# 可以指定更多的信息，比如加一个版本号
project ("GcServer")

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    # !!! choose your compiler on Windows
    set(CMAKE_C_COMPILER "D:/MINGW/mingw32/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "D:/MINGW/mingw32/bin/g++.exe")
else()  # in Ubuntu
    # # choose the version of cpp, C++17 or higher is needed.
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# using gdb
set(CMAKE_BUILD_TYPE "Debug")

# .exe's output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# .lib's output path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# header files' searching path
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/example)

# link libs
link_directories(${PROJECT_SOURCE_DIR}/lib)

# about rpc 
add_subdirectory(src)

# about example
add_subdirectory(example)