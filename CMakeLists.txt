cmake_minimum_required(VERSION 3.14)

project(u8cc CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variable `sources`
file(GLOB_RECURSE sources src/*.cpp src/*.hpp)
# Exclude file containing main function
set(main_source "src/u8cc.cpp")
list(REMOVE_ITEM sources ${main_source})

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_library(${PROJECT_NAME}_lib STATIC ${sources})

if (MSVC)
    target_compile_options(${PROJECT_NAME}_lib PRIVATE /EHsc /W4 /WX)
    target_link_options(${PROJECT_NAME}_lib PRIVATE /EHsc /W4 /WX)
else ()
    target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_link_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif ()

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(${PROJECT_NAME}_lib PUBLIC src)

# add the executable target
add_executable(${PROJECT_NAME} ${main_source})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

###############################################################################
## dependencies ###############################################################
###############################################################################

## this defines the variables Boost_LIBRARIES that contain all library names
## that we need to link to
#find_package(Boost 1.64.0 REQUIRED)
#
#if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIR})
#    add_definitions("-DHAS_BOOST")
#endif ()
#
#target_link_libraries(${PROJECT_NAME}_lib PUBLIC
#        ${Boost_LIBRARIES}
#        # here you can add any library dependencies
#        )

#file(DOWNLOAD "https://raw.githubusercontent.com/aantron/better-enums/0.11.3/enum.h" "lib/better-enums/enum.h")
#target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/lib)

###############################################################################
## testing ####################################################################
###############################################################################

enable_testing()
include(GoogleTest)
add_subdirectory(test)

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS ${PROJECT_NAME} DESTINATION install)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "u8cc")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
