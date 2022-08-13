cmake_minimum_required(VERSION 3.23)
project(Asio_learning)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE -std=c++20 -pthread")
endif()

include(FetchContent)

FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio
        GIT_TAG asio-1-24-0
        UPDATE_DISCONNECTED 1
)

FetchContent_Populate(asio)

include_directories(${asio_SOURCE_DIR}/asio/include/)

if(WIN32 AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    link_libraries(ws2_32 wsock32)
endif()

add_subdirectory(Simple_Example)
add_subdirectory(Echo_application/Client)
add_subdirectory(Echo_application/Server)
