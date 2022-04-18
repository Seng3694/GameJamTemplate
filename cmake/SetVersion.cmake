set(HEADER_FILE "include/Version.hpp")
set(CACHE_FILE "BuildNumberCache.txt")

if(NOT DEFINED MAJOR_VERSION)
    set(MAJOR_VERSION 0)
endif()
if(NOT DEFINED MINOR_VERSION)
    set(MINOR_VERSION 0)
endif()

if(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} BUILD_NUMBER)
    math(EXPR BUILD_NUMBER "${BUILD_NUMBER}+1")
else()
    set(BUILD_NUMBER "1")
endif()

message("${CMAKE_SOURCE_DIR}")

configure_file(cmake/BuildNumberCache.txt.in ${CACHE_FILE})
configure_file(cmake/Version.hpp.in ${HEADER_FILE})