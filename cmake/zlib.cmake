include(FetchContent)

FetchContent_Declare(
    zlib-cmake
    URL https://github.com/jimmy-park/zlib-cmake/archive/main.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    FIND_PACKAGE_ARGS NAMES zlib ZLIB
)

FetchContent_MakeAvailable(zlib-cmake)