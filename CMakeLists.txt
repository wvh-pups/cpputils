cmake_minimum_required(VERSION 3.16)
project(cpp-utils CXX C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "-Wall -static")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS "-Wall -static")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(include)

add_library(c++utils SHARED
        src/shared.cpp
        include/utils/shared.hpp
        src/vector.cpp
        include/utils/vector.hpp
        src/string.cpp
        include/utils/string.hpp
        src/memory.cpp
        include/utils/memory.hpp
)

add_executable(c++utils_test
    test.cpp
)

target_link_libraries(c++utils_test c++utils "-Wl,-allow-multiple-definition")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(c++utils_test PRIVATE DEBUG=1)
endif()

add_test(c++utils_test $<TARGET_FILE:c++utils_test>)