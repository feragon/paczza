#include <iostream>
#include <game/jeu.h>
#include <ui/menu/menubutton.h>
#include <game/pacmangame.h>
#include <data/gamedataimpl.h>
#include "mainmenu.h"
#include "credits.h"
#include "tutorialview.h"
#include "pacmangameview.h"

MainMenu::MainMenu(sf::RenderWindow* window, FenetreJeu* f) :
    Menu(window, f) {

    _titreTexture.loadFromFile("res/titre.png");
    _titreSprite.setTexture(_titreTexture);
    _titreSprite.setPosition(window->getSize().x / 2 - _titreSprite.getGlobalBounds().width / 2, 120);

    addItem(new MenuButton(L"Nouvelle partie", std::bind(&MainMenu::onNewGameSelected, this)));
    addItem(new MenuButton(L"Aide", std::bind(&MainMenu::onHelpSelected, this)));
    addItem(new MenuButton(L"Crédits", std::bind(&MainMenu::onCreditsSelected, this)));
    addItem(new MenuButton(L"Quitter", std::bind(&MainMenu::onExitSelected, this)));
}

void MainMenu::onNewGameSelected() {
    fenetreJeu()->changerVue(new PacmanGameView(window(), fenetreJeu(), generateGame()));
}

void MainMenu::onCreditsSelected() {
    fenetreJeu()->changerVue(new Credits(window(), fenetreJeu()));
}

void MainMenu::onExitSelected() {
    window()->close();
}

void MainMenu::onHelpSelected() {
    fenetreJeu()->changerVue(new TutorialView(window(), fenetreJeu(), generateGame()));
}

SharedPtr<Jeu> MainMenu::generateGame() {
    GameDataImpl gd;
    SharedPtr<Board<Element>> board;
    gd.genererPlateau(board.get());

    return SharedPtr<PacmanGame>(board, &gd);
}

void MainMenu::render(double timeElapsed) {
    Menu::render(timeElapsed);
    window()->draw(_titreSprite);
}
