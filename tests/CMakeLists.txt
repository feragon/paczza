cmake_minimum_required(VERSION 3.6)
project(paczza)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
)

include_directories(catch)

add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests game)