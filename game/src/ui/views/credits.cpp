#include <ui/resourceloader.h>
#include "credits.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <codecvt>

Credits::Credits(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f) {

    setFond(EMPTY_CELL);
}

void Credits::resize(const sf::Vector2f& size) {
    View::resize(size);

    wchar_t buf[BUFSIZ];
    unsigned int n = 0;

    std::wifstream creditsFile("res/credits.txt", std::ios::in);
    creditsFile.imbue(std::locale(creditsFile.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    while (!creditsFile.eof()) {
        creditsFile.getline(buf, BUFSIZ);
        sf::Text text(buf, ResourceLoader::getFont(PIXELLARI), 32);

        double ratio = text.getLocalBounds().width / window()->getView().getSize().x;

        if(ratio > 1) {
            std::wstring str(buf);
            size_t textLen = str.size();
            double lineLength = ceil(textLen / ratio) - 1;

            for(int i = 0; i < textLen; i += lineLength) {
                text = sf::Text(str.substr(i, lineLength), ResourceLoader::getFont(PIXELLARI), 32);
                text.setPosition(0, 36 * n);
                _texts.push_back(text);
                n++;
            }
        }
        else {
            text.setPosition(0, 36 * n);
            _texts.push_back(text);
            n++;
        }
    }

    creditsFile.close();
}

void Credits::render(double timeElapsed) {
    View::render(timeElapsed);

    for(sf::Text text : _texts) {
        window()->draw(text);
    }
}

void Credits::onEvent(const sf::Event& event) {

}
