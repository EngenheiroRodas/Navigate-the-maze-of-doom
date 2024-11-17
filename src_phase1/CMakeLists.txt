# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Name of your project
project(NavigateProject LANGUAGES C)

# Add the source files to the project
set(SOURCES
    navigate.c
    builder.c
    navigation.c
    processing.c
)

# Add an executable named 'navigate' from the source files
add_executable(navigate ${SOURCES})

# Add compilation flags
target_compile_options(navigate PRIVATE -O3 -Wall)
