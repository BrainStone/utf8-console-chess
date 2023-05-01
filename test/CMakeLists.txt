# Build output setup
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

################################
# GTest
################################
project(googletest-git NONE)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

################################
# Tests
################################
project(constexpr_cmath_test CXX)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})

# Add test cpp file
add_executable(${PROJECT_NAME} test_trig.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main constexpr_cmath)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")
