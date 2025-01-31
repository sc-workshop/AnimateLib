file(GLOB_RECURSE SOURCES source/*.h source/*.hpp source/*.cpp)

set(TARGET animate-lib)
add_library(${TARGET} STATIC ${SOURCES})	
add_library(Adobe::AnimateLib ALIAS ${TARGET})

target_include_directories(${TARGET} PUBLIC source)
target_link_libraries(${TARGET} PUBLIC
    wk::core
    pugixml::pugixml
    zip
    ZLIB::ZLIB
)

wk_project_setup(${TARGET})