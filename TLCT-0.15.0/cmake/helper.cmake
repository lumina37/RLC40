include(GNUInstallDirs)

function(install_target name)
    install(TARGETS ${name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endfunction()

find_package(Git QUIET)
if (GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE TLCT1_GIT_TAG
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif ()
if (NOT TLCT1_GIT_TAG)
    set(TLCT1_GIT_TAG "unknown")
endif ()

set(TLCT1_COMPILE_INFO "<tag:${TLCT1_GIT_TAG}> by [${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_SYSTEM_PROCESSOR})]")
set(TLCT1_TESTDATA_DIR "${tlct1-test-data_SOURCE_DIR}")

set(TLCT1_CONFIGURE_DIR "${PROJECT_SOURCE_DIR}/src/include/tlct1/common")
configure_file("${TLCT1_CONFIGURE_DIR}/cmake.h.in" "${TLCT1_CONFIGURE_DIR}/cmake.h" @ONLY)
