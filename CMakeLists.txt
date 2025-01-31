cmake_minimum_required(VERSION 3.22)

# workspace
project(animate-lib)

# dependencies
include(FetchContent)
include(cmake/core.cmake)
include(cmake/xml.cmake)
include(cmake/zip.cmake)
include(cmake/zlib.cmake)

# projects
add_subdirectory(animate-lib)
add_subdirectory(tool)