#include <game/jeu.h>
#include <game/teleporter.h>
#include "gamedataimpl.h"
#include <game/superpoint.h>

void GameDataImpl::placePlayers(Jeu* game) const {
    Sommet<Case<Element>>* playerPos = game->plateau()->sommet(Position<>(3,5));
    playerPos->contenu().setElement(nullptr);
    game->player().setPosition(playerPos);
    game->player().setDirection(UP);

    game->addMonster(game->plateau()->sommet(Position<>(6,4)));
    game->addMonster(game->plateau()->sommet(Position<>(6,5)));
    game->addMonster(game->plateau()->sommet(Position<>(7,4)));
    game->addMonster(game->plateau()->sommet(Position<>(7,5)));
}

void GameDataImpl::placeElements(Jeu* game) const {
    Sommet<Case<Element>>* s_t1 = game->plateau()->sommet(Position<>(6,1));
    Sommet<Case<Element>>* s_t2 = game->plateau()->sommet(Position<>(6,8));
    Teleporter t1(s_t2);
    Teleporter t2(s_t1);

    s_t1->contenu().setElement(&t1);
    s_t2->contenu().setElement(&t2);

    //Placement des points
    try {
        game->plateau()->placerElementHasard(SuperPoint(50, game));
        game->plateau()->placerElementHasard(SuperPoint(50, game));
        game->plateau()->placerElementHasard(SuperPoint(50, game));
        game->plateau()->placerElementHasard(SuperPoint(50, game));
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    Point element(10);
    for(Liste<Sommet<Case<Element>>>* l = game->plateau()->sommets(); l; l = l->next) {
        if(l->value->degre() > 0 &&
           !l->value->contenu().element()) {

            l->value->contenu().setElement(&element);
        }
    }
}

GameData* GameDataImpl::clone() const {
    return new GameDataImpl();
}

void GameDataImpl::genererPlateau(Board<Element>* board) const {
    int width = 13;
    int height = 8;

    //Création des sommets
    for(int k = (width * height) - 1; k >= 0; k--) {
        board->creeSommet(Case<Element>(Position<>((k % width) + 1, (k / width) + 1), nullptr));
    }

    //Maison des Monstres
    board->creeArete(Chemin(-1), board->sommet(Position<>(7,4)), board->sommet(Position<>(8,4)));
    board->creeArete(Chemin(-1), board->sommet(Position<>(7,5)), board->sommet(Position<>(7,6)));
    board->creeArete(Chemin(-1), board->sommet(Position<>(6,5)), board->sommet(Position<>(5,5)));
    board->creeArete(Chemin(-1), board->sommet(Position<>(6,4)), board->sommet(Position<>(6,3)));

    //Diags
    board->creeArete(Chemin(0), board->sommet(Position<>(1,1)), board->sommet(Position<>(2,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(1,8)), board->sommet(Position<>(2,7)));
    board->creeArete(Chemin(0), board->sommet(Position<>(7,2)), board->sommet(Position<>(8,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(7,7)), board->sommet(Position<>(8,6)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,1)), board->sommet(Position<>(12,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,8)), board->sommet(Position<>(12,7)));


    for(int j = 1; j < 8; j++)
        board->creeArete(Chemin(0), board->sommet(Position<>(1,j)), board->sommet(Position<>(1,j+1)));

    board->creeArete(Chemin(0), board->sommet(Position<>(2,1)), board->sommet(Position<>(2,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,8)), board->sommet(Position<>(2,7)));
    board->creeArete(Chemin(0), board->sommet(Position<>(1,4)), board->sommet(Position<>(2,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(1,5)), board->sommet(Position<>(2,5)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,4)), board->sommet(Position<>(2,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,5)), board->sommet(Position<>(2,6)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,1)), board->sommet(Position<>(3,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,8)), board->sommet(Position<>(3,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,3)), board->sommet(Position<>(3,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(2,6)), board->sommet(Position<>(3,6)));

    for(int j = 2; j < 7; j++)
        board->creeArete(Chemin(0), board->sommet(Position<>(3,j)), board->sommet(Position<>(3,j+1)));

    for(int i = 2; i < 13; i++) {
        board->creeArete(Chemin(0), board->sommet(Position<>(i, 2)), board->sommet(Position<>(i + 1, 2)));
        board->creeArete(Chemin(0), board->sommet(Position<>(i, 7)), board->sommet(Position<>(i + 1, 7)));
    }

    board->creeArete(Chemin(0), board->sommet(Position<>(3,4)), board->sommet(Position<>(4,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(3,5)), board->sommet(Position<>(4,5)));

    for(int j = 1; j < 8; j++)
        if(j!=4) board->creeArete(Chemin(0), board->sommet(Position<>(4,j)), board->sommet(Position<>(4,j+1)));


    board->creeArete(Chemin(0), board->sommet(Position<>(6,1)), board->sommet(Position<>(6,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(6,7)), board->sommet(Position<>(6,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,1)), board->sommet(Position<>(8,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,7)), board->sommet(Position<>(8,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,1)), board->sommet(Position<>(9,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,7)), board->sommet(Position<>(9,8)));

    for(int j = 3; j < 6; j++) {
        board->creeArete(Chemin(0), board->sommet(Position<>(5, j)), board->sommet(Position<>(5, j+1)));
        board->creeArete(Chemin(0), board->sommet(Position<>(8, j)), board->sommet(Position<>(8, j+1)));
    }

    for(int i = 4; i < 8; i++) {
        board->creeArete(Chemin(0), board->sommet(Position<>(i, 3)), board->sommet(Position<>(i+1, 3)));
        board->creeArete(Chemin(0), board->sommet(Position<>(i, 6)), board->sommet(Position<>(i+1, 6)));
    }

    board->creeArete(Chemin(0), board->sommet(Position<>(6,2)), board->sommet(Position<>(6,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(6,6)), board->sommet(Position<>(6,7)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,1)), board->sommet(Position<>(9,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,8)), board->sommet(Position<>(9,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,4)), board->sommet(Position<>(9,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(8,5)), board->sommet(Position<>(9,5)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,4)), board->sommet(Position<>(9,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,5)), board->sommet(Position<>(9,6)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,3)), board->sommet(Position<>(10,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(9,6)), board->sommet(Position<>(10,6)));

    board->creeArete(Chemin(0), board->sommet(Position<>(12,8)), board->sommet(Position<>(13,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,1)), board->sommet(Position<>(13,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(3,1)), board->sommet(Position<>(4,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(3,8)), board->sommet(Position<>(4,8)));

    for(int j = 1; j < 8; j++)
        board->creeArete(Chemin(0), board->sommet(Position<>(10,j)), board->sommet(Position<>(10,j+1)));

    board->creeArete(Chemin(0), board->sommet(Position<>(10,4)), board->sommet(Position<>(11,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(10,5)), board->sommet(Position<>(11,5)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,4)), board->sommet(Position<>(12,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,5)), board->sommet(Position<>(12,5)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,2)), board->sommet(Position<>(12,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,3)), board->sommet(Position<>(12,4)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,5)), board->sommet(Position<>(12,6)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,6)), board->sommet(Position<>(12,7)));
    board->creeArete(Chemin(0), board->sommet(Position<>(10,1)), board->sommet(Position<>(11,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,1)), board->sommet(Position<>(12,1)));
    board->creeArete(Chemin(0), board->sommet(Position<>(10,8)), board->sommet(Position<>(11,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,8)), board->sommet(Position<>(12,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(13,1)), board->sommet(Position<>(13,2)));
    board->creeArete(Chemin(0), board->sommet(Position<>(13,2)), board->sommet(Position<>(13,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(13,6)), board->sommet(Position<>(13,7)));
    board->creeArete(Chemin(0), board->sommet(Position<>(13,7)), board->sommet(Position<>(13,8)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,3)), board->sommet(Position<>(13,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(12,6)), board->sommet(Position<>(13,6)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,3)), board->sommet(Position<>(12,3)));
    board->creeArete(Chemin(0), board->sommet(Position<>(11,6)), board->sommet(Position<>(12,6)));
}
