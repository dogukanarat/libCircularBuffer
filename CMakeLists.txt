cmake_minimum_required(VERSION 3.6)

project(
    LibCircularBuffer
    VERSION 0.1
    LANGUAGES C CXX
)

option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if (ENABLE_TEST_COVERAGE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("====== Building with coverage flags")

    set(GCC_COVERAGE_COMPILE_FLAGS "--coverage -g -O0")
    set(GCC_COVERAGE_LINK_FLAGS    "--coverage -g")

    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
else (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("====== Building without coverage flags")
endif (ENABLE_TEST_COVERAGE AND CMAKE_BUILD_TYPE STREQUAL "Debug")

add_library(
    CircularBuffer
)

target_sources(
    CircularBuffer
    PRIVATE
        Src/CircularBuffer.c
)

target_include_directories(
    CircularBuffer
    PUBLIC
        Inc
)

target_include_directories(
    CircularBuffer 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS CircularBuffer
    EXPORT Libraries-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Inc
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libCircularBuffer
    FILES_MATCHING PATTERN "*.h"
)

enable_testing()
add_subdirectory(Tests)
