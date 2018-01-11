cmake_minimum_required(VERSION 3.6)
project(paczza)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SOURCE_FILES
        src/main.cpp
        src/ui/fenetrejeu.cpp src/ui/fenetrejeu.h src/game/jeu.cpp src/game/jeu.h src/game/joueur.cpp src/game/joueur.h src/board/position.cpp src/board/position.h src/ui/spriteloader.cpp src/ui/spriteloader.h src/ui/views/view.cpp src/ui/views/view.h src/ui/views/mainmenu.cpp src/ui/views/mainmenu.h src/ui/views/menu.cpp src/ui/views/menu.h)

find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

include_directories(src)

add_executable(paczza ${SOURCE_FILES})
target_link_libraries(paczza ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_library(game ${SOURCE_FILES})
target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})