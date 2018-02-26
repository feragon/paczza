#include <game/direction.h>
#include "changedirectioncommand.h"

ChangeDirectionCommand::ChangeDirectionCommand(Jeu* game, Direction newDirection) {
    _game = game;
    _newDirection = newDirection;
}

void ChangeDirectionCommand::execute() {
    _game->setDirection(_newDirection);
}
