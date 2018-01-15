#include <ui/resourceloader.h>
#include "credits.h"
#include <fstream>

Credits::Credits(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f) {

    setFond(EMPTY_CELL);
    char buf[BUFSIZ];
    unsigned int n = 0;

    std::fstream creditsFile("res/credits.txt", std::ios::in);

    while (!creditsFile.eof()) {
        creditsFile.getline(buf, BUFSIZ);
        sf::Text text(buf, ResourceLoader::getFont(PIXELLARI), 32);
        text.setPosition(0, 36 * n);
        _texts.push_back(text);
        n++;
    }
}

void Credits::resize(const sf::Vector2f& size) {
    View::resize(size);
}

void Credits::render() {
    View::render();

    for(sf::Text text : _texts) {
        window()->draw(text);
    }
}

void Credits::onEvent(const sf::Event& event) {

}
