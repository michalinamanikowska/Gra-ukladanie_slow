cmake_minimum_required(VERSION 3.10)

project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(server server.cpp dictionary.txt)
