set(TLCT2_LIB_NAME tlc)

add_library(${TLCT2_LIB_NAME} INTERFACE)
add_library(tlct2::lib ALIAS ${TLCT2_LIB_NAME})
target_compile_features(${TLCT2_LIB_NAME} INTERFACE cxx_std_20)
target_include_directories(${TLCT2_LIB_NAME} INTERFACE
        "${PROJECT_SOURCE_DIR}/src/include"
        ${OpenCV_INCLUDE_DIRS}
        "${pugixml_SOURCE_DIR}/src"
)
target_link_libraries(${TLCT2_LIB_NAME} INTERFACE
        ${OpenCV_LIBS}
        $<$<NOT:$<BOOL:${PUGIXML_HEADER_ONLY}>>:pugixml>
)
