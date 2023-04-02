include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG  release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

option(INSTALL_GTEST "Enable installation of googletest." OFF)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(
    LibCircularBufferUnitTest
    Main.cpp
    LibCircularBuffer.cpp
    LibCircularBufferExt.cpp
)

target_compile_definitions(LibCircularBufferUnitTest PUBLIC CTEST)

target_link_libraries(
    LibCircularBufferUnitTest
        gtest_main
        CircularBuffer
)

gtest_discover_tests(LibCircularBufferUnitTest
    PROPERTIES
        LABELS "unit"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
)
