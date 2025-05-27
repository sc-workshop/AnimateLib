cmake_minimum_required(VERSION 3.22)

# workspace
project(animate-lib)

# options
option(AN_BUILD_TOOL "Build test tool" OFF)


# dependencies
include(FetchContent)
include(cmake/core.cmake)
include(cmake/xml.cmake)
include(cmake/zip.cmake)
include(cmake/zlib.cmake)

# projects
add_subdirectory(animate-lib)

if(AN_BUILD_TOOL)
	add_subdirectory(tool)
endif()