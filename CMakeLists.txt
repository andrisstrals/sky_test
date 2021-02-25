cmake_minimum_required(VERSION 3.5)

project(testRewardsService LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)

include_directories(./include ./external)

add_executable(${PROJECT_NAME} test/tst_testrewardsservice.cpp test/main.cpp)


if (DEFINED ENV{CATCH_INCLUDE_DIR})
    set(CATCH_INCLUDE_DIR $ENV{CATCH_INCLUDE_DIR})
else ()
    set(CATCH_INCLUDE_DIR "") # set by Qt Creator wizard
endif ()
if (CATCH_INCLUDE_DIR STREQUAL "")
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
elseif (EXISTS ${CATCH_INCLUDE_DIR})
    include_directories(${CATCH_INCLUDE_DIR})
endif ()
