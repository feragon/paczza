#include "buttontrigger.h"
#include "menubutton.h"

ButtonTrigger::ButtonTrigger(MenuButton* menuButton) {
    _menuButton = menuButton;
}

void ButtonTrigger::execute() {
    _menuButton->executeCallback();
}
