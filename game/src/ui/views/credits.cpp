#include <ui/resourceloader.h>
#include "credits.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <codecvt>

Credits::Credits(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f) {

    _position = 0;
    setFond(SPACE);
}

void Credits::resize(const sf::Vector2f& size) {
    View::resize(size);

    _texts.clear();
    createText(window()->getView().getSize().y - _position);
}

void Credits::render(double timeElapsed) {
    View::render(timeElapsed);
    updateText(timeElapsed * 50);

    for(const sf::Text& text : _texts) {
        window()->draw(text);
    }
}

void Credits::onEvent(const sf::Event& event) {

}

void Credits::updateText(float yOffset) {
    _position += yOffset;

    for(sf::Text& text : _texts) {
        text.move(0, -yOffset);
    }
}

void Credits::createText(float initialYPosition) {
    wchar_t buf[BUFSIZ];
    float nextY = initialYPosition;

    std::wifstream creditsFile("res/credits.txt", std::ios::in);
    creditsFile.imbue(std::locale(creditsFile.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    while (!creditsFile.eof()) {
        creditsFile.getline(buf, BUFSIZ);
        sf::Text text(buf, ResourceLoader::getFont(KONGTEXT), 32);

        double ratio = text.getLocalBounds().width / (window()->getView().getSize().x - 50);

        if(ratio > 1) {
            std::wstring str(buf);
            size_t textLen = str.size();
            unsigned long lineLength = ceil(textLen / ratio) - 1;
            unsigned long esp;
            std::string charEsp(" ");

            long i = 0;
            while(i < str.size()) {

                esp = i+lineLength;
                while(esp < str.size()-1 && esp > i && str.at(esp) != charEsp.at(0))
                    esp--;

                text = sf::Text(str.substr(i, esp-i), ResourceLoader::getFont(KONGTEXT), 32);

                text.setPosition(25 + (window()->getView().getSize().x - 50 - text.getLocalBounds().width)/2, nextY);
                text.setColor(sf::Color(255,255,0));
                nextY += text.getCharacterSize() + 2;

                _texts.push_back(text);

                i = esp + 1;
            }
        }
        else {
            text.setPosition(25 + (window()->getView().getSize().x - 50 - text.getLocalBounds().width)/2, nextY);
            text.setColor(sf::Color(255,255,0));
            _texts.push_back(text);
            nextY += text.getCharacterSize() + 2;
        }
    }

    creditsFile.close();
}
