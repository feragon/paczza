#pragma once

#include <board/position.h>
#include <game/pacman.h>
#include <graph/arete.h>
#include "board/chemin.h"

class BoardListener {
    public:
        /**
         * @brief Fonction appelée avant un déplacement du joueur
         * @param player Joueur concerné
         */
        virtual void playerMovementBegin(Pacman* player) = 0;

        /**
         * @brief Fonction appelée lorsque les données d'une arête ont été mises à jour
         * @param edge Arête concernée
         */
        virtual void updateEdge(Arete<Chemin, Case>* edge) = 0;

        /**
         * @brief Fonction appelée lorsqu'un sommet a été mis à jour
         * @param vertice Sommet concerné
         */
        virtual void updateVertice(Sommet<Case>* vertice) = 0;

        /**
         * @brief Fonction appelée avant un nouveau tour
         */
        virtual void onNewTurn() = 0;
};