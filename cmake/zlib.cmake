# https://github.com/diasurgical/devilutionX/blob/master/3rdParty/zlib/CMakeLists.txt

set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)

include(FetchContent)
FetchContent_Declare(zlib
    URL https://www.zlib.net/zlib-1.2.13.tar.gz
        https://www.zlib.net/fossils/zlib-1.2.13.tar.gz
        https://github.com/madler/zlib/releases/download/v1.2.13/zlib-1.2.13.tar.gz
    URL_HASH MD5=9b8aa094c4e5765dabf4da391f00d15c
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(zlib)

if(WK_BUILD_SHARED)
    add_library(ZLIB::ZLIB ALIAS zlib)
    target_include_directories(zlib INTERFACE ${zlib_BINARY_DIR} ${zlib_SOURCE_DIR})
else()
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
    target_include_directories(zlibstatic INTERFACE ${zlib_BINARY_DIR} ${zlib_SOURCE_DIR})
endif()

# 1. Set the variables that are usually set by FindZLIB.cmake.
# 2. Add the module that stubs out `find_package(ZLIB ...)` calls.
set(ZLIB_FOUND ON)
set(ZLIB_LIBRARY ZLIB::ZLIB)
set(ZLIB_LIBRARIES ZLIB::ZLIB)
set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
set(ZLIB_INCLUDE_DIRS ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})