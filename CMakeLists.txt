cmake_minimum_required(VERSION 3.10)
project(fibpass)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)


if(LINUX)
    target_link_libraries(fibpass PRIVATE crypt)
endif()
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
