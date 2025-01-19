function(tlct1_add_executable name srcs)
    add_executable(${name} ${srcs})
    target_link_libraries(${name} PRIVATE tlct1 argparse)
    target_include_directories(${name} PRIVATE ${argparse_SOURCE_DIR}/include)
    target_compile_definitions(${name} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)

    install_target(${name})
endfunction()

tlct1_add_executable(RLC40 "RLC40.cpp")
tlct1_add_executable(dbg_draw "dbg_draw.cpp")
tlct1_add_executable(get_center "get_center.cpp")
