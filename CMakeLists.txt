cmake_minimum_required(VERSION 3.15)

project(uWSExample)

set(CMAKE_CXX_STANDARD 20)

find_package(unofficial-uwebsockets CONFIG REQUIRED)

add_executable(uWSExample src/main.cpp)
target_link_libraries(uWSExample PRIVATE unofficial::uwebsockets::uwebsockets)
