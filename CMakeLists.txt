cmake_minimum_required(VERSION 3.15)

project(app_42)
ADD_LIBRARY(LibsModule src/server.cpp)

add_subdirectory(thirdparty/curlpp)
include_directories(thirdparty/curlpp/include, include)
target_link_libraries(LibsModule PRIVATE curlpp)

add_executable(app src/main.cpp)
target_link_libraries(app LibsModule)