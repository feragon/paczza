#pragma once

#include <game/direction.h>
#include <board/chemin.h>
#include <board/case.h>
#include <graph/arete.h>

/**
 * @brief Donne la direction d'un vecteur
 * @param depart Origine
 * @param fin Fin
 * @return Direction
 */
Direction getDirection(const Position<>& depart, const Position<>& fin);