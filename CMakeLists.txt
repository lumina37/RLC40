cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(RLC40
        VERSION 4.0
        LANGUAGES CXX
)

set(TLCT0_PUGIXML_PATH ${PROJECT_SOURCE_DIR}/pugixml-1.14 CACHE STRING "" FORCE)
set(TLCT1_PUGIXML_PATH ${PROJECT_SOURCE_DIR}/pugixml-1.14 CACHE STRING "" FORCE)
set(TLCT2_PUGIXML_PATH ${PROJECT_SOURCE_DIR}/pugixml-1.14 CACHE STRING "" FORCE)

set(TLCT0_HEADER_ONLY ON CACHE BOOL "" FORCE)
set(TLCT1_HEADER_ONLY ON CACHE BOOL "" FORCE)
set(TLCT2_HEADER_ONLY ON CACHE BOOL "" FORCE)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")

add_subdirectory(TLCT-0.12.0)
add_subdirectory(TLCT-0.15.0)
add_subdirectory(TLCT-0.15.2.0)

FetchContent_Declare(
        argparse
        URL ${PROJECT_SOURCE_DIR}/argparse-3.1
)
FetchContent_MakeAvailable(argparse)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE argparse tlct0 tlct1 tlct2::lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${argparse_SOURCE_DIR}/include)
