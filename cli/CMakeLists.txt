cmake_minimum_required(VERSION 3.15)

project(calc)
ADD_LIBRARY(LibsModule src/parser.cpp src/sender.cpp)

add_subdirectory(thirdparty/curlpp)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/curlpp/include ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(LibsModule PRIVATE curlpp)

add_executable(calc src/main.cpp)
target_link_libraries(calc LibsModule)