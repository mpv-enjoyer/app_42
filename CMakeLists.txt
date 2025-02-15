cmake_minimum_required(VERSION 3.15)
project(app_42 CXX)

include(CheckIncludeFileCXX)
include_directories(include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR src)
FILE(GLOB SOURCES ${SRC_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_sources(${PROJECT_NAME} PRIVATE ${SRC_DIR})