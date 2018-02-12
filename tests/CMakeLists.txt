cmake_minimum_required(VERSION 3.6)
project(paczza)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/testliste.cpp src/testgraphe.cpp src/testastar.cpp src/testsharedptr.cpp)

include_directories(catch)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../game/src)

add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests game)