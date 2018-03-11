#include <ui/resourceloader.h>
#include "credits.h"
#include "updatecreditspeed.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <codecvt>
#include <SFML/Window/Event.hpp>
#include <ui/fenetrejeu.h>

Credits::Credits(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f) {

    _position = 0;
    _speed = 50;
    setFond(SPACE);

    SharedPtr<UpdateCreditSpeed> up(this, -400);
    SharedPtr<UpdateCreditSpeed> fast(this, 400);
    SharedPtr<UpdateCreditSpeed> normal(this, 50);

    setKeyPressedCommand(sf::Keyboard::Up, up);
    setKeyPressedCommand(sf::Keyboard::Down, fast);
    setKeyPressedCommand(sf::Keyboard::Space, fast);

    setKeyReleasedCommand(sf::Keyboard::Up, normal);
    setKeyReleasedCommand(sf::Keyboard::Down, normal);
    setKeyReleasedCommand(sf::Keyboard::Space, normal);

    if (_music.openFromFile("res/sounds/ForTheDamagedCoda.wav")) {
        _music.setLoop(true);
        _music.setVolume(60);
        _music.play();
    }
}

void Credits::resize(const sf::Vector2f& size) {
    View::resize(size);

    _texts.clear();
    createText(window()->getView().getSize().y - _position);
}

void Credits::render(double timeElapsed) {
    View::render(timeElapsed);
    updateText(timeElapsed * _speed);
    bool creditsOver = true;

    for(const MultipleFontText& text : _texts) {
        window()->draw(text);
        if(text.getPosition().y > -60) creditsOver = false;
    }

    if(creditsOver)
        fenetreJeu()->vuePrecedente();
}

void Credits::onEvent(const sf::Event& event) {
    try {
        manageEvent(event);
    }
    catch (UnknownCommand& e) {

    }
}

void Credits::updateText(float yOffset) {
    _position += yOffset;

    for(MultipleFontText& text : _texts) {
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
        MultipleFontText text(buf, ResourceLoader::getFont(KONGTEXT), 32);
        text.addFont(1000, 10000000, ResourceLoader::getFont(DOCOMO));
        text.addFont(L'0', L'9', ResourceLoader::getFont(DOCOMO));

        double ratio = text.bounds().width / (window()->getView().getSize().x - 50);

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

                text = MultipleFontText(str.substr(i, esp-i), ResourceLoader::getFont(KONGTEXT), 32);
                text.addFont(1000, 10000000, ResourceLoader::getFont(DOCOMO));
                text.addFont(L'0', L'9', ResourceLoader::getFont(DOCOMO));

                text.setPosition(25 + (window()->getView().getSize().x - 50 - text.bounds().width)/2, nextY);
                text.setColor(sf::Color(255,255,0));
                nextY += text.fontSize() + 2;

                _texts.push_back(text);

                i = esp + 1;
            }
        }
        else {
            text.setPosition(25 + (window()->getView().getSize().x - 50 - text.bounds().width)/2, nextY);
            text.setColor(sf::Color(255,255,0));
            _texts.push_back(text);
            nextY += text.fontSize() + 2;
        }
    }

    creditsFile.close();
}

void Credits::setSpeed(int speed) {
    _speed = speed;
}
