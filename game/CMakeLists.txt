cmake_minimum_required(VERSION 3.6)
project(paczza)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SOURCE_FILES
        src/main.cpp
        src/ui/fenetrejeu.cpp src/ui/fenetrejeu.h src/game/jeu.cpp src/game/jeu.h src/game/player.cpp src/game/player.h src/graph/position.cpp src/graph/position.h src/ui/resourceloader.cpp src/ui/resourceloader.h src/ui/views/view.cpp src/ui/views/view.h src/ui/views/mainmenu.cpp src/ui/views/mainmenu.h src/ui/menu/menu.cpp src/ui/menu/menu.h src/graph/graphe.h src/graph/sommet.h src/graph/arete.h src/ui/views/boardview.cpp src/ui/views/boardview.h src/board/case.cpp src/board/case.h src/board/chemin.cpp src/board/chemin.h src/ui/menu/menuitem.h src/ui/menu/menubutton.cpp src/ui/menu/menubutton.h src/ui/views/credits.cpp src/ui/views/credits.h src/ui/drawables/animatedsprite.cpp src/ui/drawables/animatedsprite.h src/graph/identifiable.h src/graph/identifiable.cpp src/graph/conteneur.h src/board/board.cpp src/board/board.h src/graph/liste.h src/board/element.h src/board/point.cpp src/board/point.h src/board/element.cpp src/game/monstermanager.h src/game/monster.cpp src/game/monster.h src/game/pacman.cpp src/game/pacman.h src/game/monstermanager.cpp src/game/dumbmonstermanager.cpp src/game/dumbmonstermanager.h)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

include_directories(src)

add_executable(paczza ${SOURCE_FILES})
target_link_libraries(paczza ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_library(game ${SOURCE_FILES} src/sprite.h src/fonts.h)
target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})