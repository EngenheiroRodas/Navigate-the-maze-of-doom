cmake_minimum_required(VERSION 3.30)
project(NavigateProject LANGUAGES C)

# Add the source files
set(SOURCES
    main.c
    graph.c
    visualization.c
)

# Add the executable
add_executable(visual ${SOURCES})

# Link libraries in the correct order
target_link_libraries(visual PRIVATE GL GLU glut m)

# Create custom targets for debug and release
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
)

add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
)

# Default compile options (Release)
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(visual PRIVATE -O3 -Wall)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(visual PRIVATE -g -Wall)
endif()
