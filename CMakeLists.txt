cmake_minimum_required(VERSION 3.10)
project(fib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(fib src/main.cpp)

target_compile_features(fib PRIVATE cxx_std_20)

target_include_directories(fib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS fib DESTINATION bin)
