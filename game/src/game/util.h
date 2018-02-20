#pragma once

#include <game/direction.h>
#include <board/chemin.h>
#include <board/case.h>
#include <graph/arete.h>

Direction getDirection(const Position<>& depart, const Position<>& fin);