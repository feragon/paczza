#include "tutorialview.h"

TutorialView::TutorialView(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f),
        _boardView(window, f, new Jeu()) {

}

void TutorialView::onEvent(const sf::Event& event) {
    _boardView.onEvent(event);
}

void TutorialView::render(double timeElapsed) {
    View::render(timeElapsed);
    _boardView.render(timeElapsed);
}

void TutorialView::resize(const sf::Vector2f& size) {
    _boardView.resize(size);
}
