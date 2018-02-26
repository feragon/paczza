#include "updatetutorialcommand.h"

UpdateTutorialCommand::UpdateTutorialCommand(TutorialView* view) {
    _view = view;
}

void UpdateTutorialCommand::execute() {
    _view->update();
}
