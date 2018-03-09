cmake_minimum_required(VERSION 3.6)
project(paczza)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SOURCE_FILES
        src/main.cpp
        src/ui/fenetrejeu.cpp
        src/ui/fenetrejeu.h
        src/game/jeu.cpp
        src/game/jeu.h
        src/game/player.cpp
        src/game/player.h
        src/board/position.h
        src/ui/resourceloader.cpp
        src/ui/resourceloader.h
        src/ui/views/view.cpp
        src/ui/views/view.h
        src/ui/views/mainmenu.cpp
        src/ui/views/mainmenu.h
        src/ui/menu/menu.cpp
        src/ui/menu/menu.h
        src/graph/graphe.h
        src/graph/sommet.h
        src/graph/arete.h
        src/ui/views/boardview.cpp
        src/ui/views/boardview.h
        src/board/case.h
        src/board/chemin.cpp
        src/board/chemin.h
        src/ui/menu/menuitem.h
        src/ui/menu/menubutton.cpp
        src/ui/menu/menubutton.h
        src/ui/views/credits.cpp
        src/ui/views/credits.h
        src/ui/drawables/animatedsprite.cpp
        src/ui/drawables/animatedsprite.h
        src/graph/identifiable.h
        src/graph/identifiable.cpp
        src/graph/conteneur.h
        src/board/board.h
        src/graph/liste.h
        src/game/element.h
        src/game/point.cpp
        src/game/point.h
        src/game/element.cpp
        src/game/monstermanager.h
        src/game/monster.cpp
        src/game/monster.h
        src/game/pacman.cpp
        src/game/pacman.h
        src/game/monstermanager.cpp
        src/game/dumbmonstermanager.cpp
        src/game/dumbmonstermanager.h
        src/game/gamelistener.h
        src/ui/drawables/multiplefonttext.cpp
        src/ui/drawables/multiplefonttext.h
        src/game/playernotinsight.h
        src/sprite.h
        src/fonts.h
        src/game/direction.h
        src/game/sensemonstermanager.cpp
        src/game/sensemonstermanager.h
        src/game/noheatededgefound.h
        src/game/noremaininglife.h
        src/game/astarfunctions.cpp
        src/game/astarfunctions.h
        src/game/astarmonstermanager.cpp
        src/game/astarmonstermanager.h
        src/game/teleporter.cpp
        src/game/teleporter.h
        src/sounds.h src/ui/views/tutorialview.cpp
        src/ui/views/tutorialview.h
        src/ui/drawables/fog.cpp
        src/ui/drawables/fog.h
        src/ui/views/gameview.cpp
        src/ui/views/gameview.h
        src/util/shared_ptr.h
        src/game/pacmangame.cpp
        src/game/pacmangame.h
        src/game/util.h
        src/game/util.cpp
        src/ui/views/pacmangameview.cpp
        src/ui/views/pacmangameview.h
        src/ui/command/command.h
        src/ui/command/commandreceiver.h
        src/ui/command/commandreceiver.cpp
        src/ui/command/unknowncommand.h
        src/ui/menu/menumoveselector.cpp
        src/ui/menu/menumoveselector.h
        src/ui/menu/buttontrigger.cpp
        src/ui/menu/buttontrigger.h
        src/astar/infosommet.h
        src/astar/etat.h
        src/util/listened.h
        src/game/nomorelevels.h
        src/ui/command/commandreceiver.cpp
        src/ui/views/updatecreditspeed.cpp
        src/ui/views/updatecreditspeed.h
        src/ui/views/changedirectioncommand.cpp
        src/ui/views/changedirectioncommand.h
        src/ui/views/startgamecommand.cpp
        src/ui/views/startgamecommand.h
        src/ui/views/updatetutorialcommand.cpp
        src/ui/views/updatetutorialcommand.h
        src/game/superpoint.cpp
        src/game/superpoint.h
        src/game/pacmandied.h
        src/util/visitable.h
        src/game/elementvisitor.h
        src/game/gamedata.h
        src/data/gamedataimpl.cpp
        src/data/gamedataimpl.h
        src/ui/transform.h
)

find_package(SFML 2 COMPONENTS graphics window system audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

include_directories(src)

add_executable(paczza ${SOURCE_FILES})
target_link_libraries(paczza ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_library(game ${SOURCE_FILES})
target_link_libraries(game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})