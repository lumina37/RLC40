include(FetchContent)

# OpenCV
find_package(OpenCV REQUIRED COMPONENTS imgcodecs imgproc)

# pugixml
set(TLCT2_PUGIXML_PATH "https://github.com/zeux/pugixml/archive/refs/tags/v1.14.tar.gz" CACHE STRING
        "Specifies the path of pugixml")
set(PUGIXML_HEADER_ONLY ON CACHE BOOL "")
set(PUGIXML_NO_XPATH ON CACHE BOOL "")
set(PUGIXML_NO_EXCEPTIONS ON CACHE BOOL "")
set(PUGIXML_NO_STL ON CACHE BOOL "")

FetchContent_Declare(
        pugixml
        DOWNLOAD_EXTRACT_TIMESTAMP ON
        URL ${TLCT2_PUGIXML_PATH}
)
FetchContent_MakeAvailable(pugixml)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(TLCT2_ARGPARSE_PATH "https://github.com/p-ranav/argparse/archive/refs/tags/v3.1.tar.gz" CACHE STRING
            "Specifies the path of argparse")
    FetchContent_Declare(
            argparse
            DOWNLOAD_EXTRACT_TIMESTAMP ON
            URL ${TLCT2_ARGPARSE_PATH}
    )
    FetchContent_MakeAvailable(argparse)
endif ()
