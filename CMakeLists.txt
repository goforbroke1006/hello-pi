cmake_minimum_required(VERSION 2.8.12)
project(hello_pi)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src/00-flash-led-test)
add_subdirectory(src/01-hello-servo)
