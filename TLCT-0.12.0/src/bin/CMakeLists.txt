function(tlct0_add_executable name srcs)
    add_executable(${name} ${srcs})
    target_link_libraries(${name} PRIVATE tlct0)
endfunction()

# tlct0_add_executable(mv "dbg_mv.cpp")
tlct0_add_executable(mv_raytrix "dbg_mv_raytrix.cpp")
