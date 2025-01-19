set(TLCT0_CONFIGURE_DIR "${PROJECT_SOURCE_DIR}/src/include/tlct0/common")
set(TLCT0_TESTDATA_DIR "${tlct0-test-data_SOURCE_DIR}")
configure_file("${TLCT0_CONFIGURE_DIR}/cmake.h.in" "${TLCT0_CONFIGURE_DIR}/cmake.h" @ONLY)
