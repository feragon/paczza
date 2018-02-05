#include <iostream>
#include <game/jeu.h>
#include <ui/menu/menubutton.h>
#include <game/astarmonstermanager.h>
#include "mainmenu.h"
#include "boardview.h"
#include "credits.h"
#include "tutorialview.h"

MainMenu::MainMenu(sf::RenderWindow* window, FenetreJeu* f) :
    Menu(window, f) {

    addItem(new MenuButton(L"Nouvelle partie", std::bind(&MainMenu::onNewGameSelected, this)));
    addItem(new MenuButton(L"Aide", std::bind(&MainMenu::onHelpSelected, this)));
    addItem(new MenuButton(L"Meilleurs scores", std::bind(&MainMenu::onHighScoreSelected, this)));
    addItem(new MenuButton(L"Crédits", std::bind(&MainMenu::onCreditsSelected, this)));
    addItem(new MenuButton(L"Quitter", std::bind(&MainMenu::onExitSelected, this)));
}

void MainMenu::onNewGameSelected() {
    Jeu* jeu = new Jeu(); //TODO: manage life
    jeu->setMonsterManager(new AStarMonsterManager(jeu->plateau()));
    fenetreJeu()->changerVue(new BoardView(window(), fenetreJeu(), jeu));
}

void MainMenu::onHighScoreSelected() {

}

void MainMenu::onCreditsSelected() {
    fenetreJeu()->changerVue(new Credits(window(), fenetreJeu()));
}

void MainMenu::onExitSelected() {
    window()->close();
}

void MainMenu::onHelpSelected() {
    fenetreJeu()->changerVue(new TutorialView(window(), fenetreJeu()));
}
