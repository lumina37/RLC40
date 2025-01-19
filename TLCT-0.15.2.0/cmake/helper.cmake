include(GNUInstallDirs)

function(install_target name)
    install(TARGETS ${name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endfunction()

set(TLCT2_COMPILE_INFO "[TLCT2 v${TLCT2_VERSION}] [OpenCV v${OpenCV_VERSION}] by [${CMAKE_CXX_COMPILER_ID} v${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_SYSTEM_PROCESSOR})]")
set(TLCT2_TESTDATA_DIR "${tlct2-test-data_SOURCE_DIR}")

set(TLCT2_CONFIGURE_DIR "${PROJECT_SOURCE_DIR}/src/include/tlct2/common")
configure_file("${TLCT2_CONFIGURE_DIR}/cmake.h.in" "${TLCT2_CONFIGURE_DIR}/cmake.h" @ONLY)
