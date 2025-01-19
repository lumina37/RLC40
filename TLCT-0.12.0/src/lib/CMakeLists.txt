set(TLCT0_LIB_NAME tlct0)
add_library(${TLCT0_LIB_NAME} INTERFACE ${TLCT0_LIB_SRCS})
set_target_properties(${TLCT0_LIB_NAME} PROPERTIES
        VERSION ${TLCT0_VERSION}
        SOVERSION ${TLCT0_VERSION}
        DEBUG_POSTFIX "-${TLCT0_VERSION}d"
        RELEASE_POSTFIX "-${TLCT0_VERSION}")
target_compile_features(${TLCT0_LIB_NAME} INTERFACE cxx_std_20)
target_include_directories(${TLCT0_LIB_NAME} INTERFACE
        ${OpenCV_INCLUDE_DIR}
        "${pugixml_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/include"
)
target_link_libraries(${TLCT0_LIB_NAME} INTERFACE
        ${OpenCV_LIBS}
        $<$<NOT:$<BOOL:${PUGIXML_HEADER_ONLY}>>:pugixml>
)
