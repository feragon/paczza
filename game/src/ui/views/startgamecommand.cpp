#include "startgamecommand.h"

StartGameCommand::StartGameCommand(PacmanGameView* view) {
    _view = view;
}

void StartGameCommand::execute() {
    _view->startGame();
}
