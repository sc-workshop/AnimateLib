# Project: animate-lib test-tool

# C++ headers and source files
set(SOURCES source/main.cpp)

set(TARGET animate-lib-test)

add_executable(${TARGET} ${SOURCES})

set_target_properties(${TARGET} PROPERTIES
    FOLDER WorkshopSDK/Animate
)

target_link_libraries(${TARGET} PRIVATE Adobe::AnimateLib)

wk_project_setup(${TARGET})
