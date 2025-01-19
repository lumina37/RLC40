cmake_minimum_required(VERSION 3.21)

include(cmake/policies.cmake)

project(TLCT0 VERSION 0.12.0 LANGUAGES CXX)

include(cmake/dependencies.cmake)
include(cmake/helper.cmake)

add_subdirectory(src)
