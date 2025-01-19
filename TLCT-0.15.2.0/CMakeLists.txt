cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(cmake/policies.cmake)

project(TLCT2
        VERSION 0.15.1.40
        LANGUAGES CXX
)

include(cmake/dependencies.cmake)
include(cmake/helper.cmake)

add_subdirectory(src)
