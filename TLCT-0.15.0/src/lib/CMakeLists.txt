set(TLCT1_LIB_NAME tlct1)

add_library(${TLCT1_LIB_NAME} INTERFACE)
target_compile_features(${TLCT1_LIB_NAME} INTERFACE cxx_std_20)
target_include_directories(${TLCT1_LIB_NAME} INTERFACE
        "${PROJECT_SOURCE_DIR}/src/include"
        ${OpenCV_INCLUDE_DIRS}
        "${pugixml_SOURCE_DIR}/src"
)
target_link_libraries(${TLCT1_LIB_NAME} INTERFACE
        ${OpenCV_LIBS}
        $<$<NOT:$<BOOL:${PUGIXML_HEADER_ONLY}>>:pugixml>
)
