#include "menumoveselector.h"
#include "menu.h"

MenuMoveSelector::MenuMoveSelector(Menu* menu, long offset) {
    _menu = menu;
    _offset = offset;
}

void MenuMoveSelector::execute() {
    _menu->updateSelector(_offset);
}
