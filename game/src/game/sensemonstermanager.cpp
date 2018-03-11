#include "sensemonstermanager.h"
#include "playernotinsight.h"
#include "noheatededgefound.h"
#include "dumbmonstermanager.h"
#include <game/jeu.h>
#include <time.h>

SenseMonsterManager::SenseMonsterManager(Jeu* game) :
        MonsterManager(game) {
    srand(time(NULL));
}

void SenseMonsterManager::moveMonster(const Monster* monster, const Position<>& playerPosition) {
    Sommet<Case<Element>>* monsterVertex = game()->plateau()->sommet(monster->position()->contenu().position());
    try {
        monsters()[monster] = nextPositionBySight(monsterVertex, playerPosition);
    }
    catch (PlayerNotInSight& e) {
        try {
            monsters()[monster] = nextPositionByHeat(monsterVertex);
        }
        catch (NoHeatedEdgeFound& f) {
            monsters()[monster] = DumbMonsterManager::getNextPosition(game()->plateau(), monsterVertex);
        }
    }
}

Position<> SenseMonsterManager::nextPositionBySight(const Sommet<Case<Element>>* monsterVertice, const Position<>& playerPosition) {
    Position<> monsterPosition = monsterVertice->contenu().position();

    if(monsterPosition == playerPosition) {
        return playerPosition;
    }

    Position<> vect = playerPosition - monsterPosition;

    int absX = abs(vect.x);
    int absY = abs(vect.y);
    if(absX != absY && vect.x != 0 && vect.y != 0) {
        throw PlayerNotInSight("Le monstre n'est pas aligné avec le joueur");
    }

    Position<> direction(0, 0);

    if(vect.x != 0) {
        direction.x = vect.x / absX;
    }

    if(vect.y != 0) {
        direction.y = vect.y / absY;
    }

    Position<> next = monsterPosition + direction;
    Liste<Sommet<Case<Element>>>* tmp = game()->plateau()->voisins(monsterVertice);
    Liste<Sommet<Case<Element>>>* neighbors = tmp;
    while(neighbors) {
        if(neighbors->value->contenu().position() == next) {
            if(next == playerPosition) {
                Liste<Sommet<Case<Element>>>::efface1(tmp);
                return monsterPosition + direction;
            }
            else {
                next = next + direction;
                neighbors = game()->plateau()->voisins(neighbors->value);
                Liste<Sommet<Case<Element>>>::efface1(tmp);
                tmp = neighbors;
            }
        }
        else {
            neighbors = neighbors->next;
        }
    }

    Liste<Sommet<Case<Element>>>::efface1(tmp);
    throw PlayerNotInSight("Il n'y a pas de chemin entre le monstre et le joueur");
}

Position<> SenseMonsterManager::nextPositionByHeat(const Sommet<Case<Element>>* monsterVertice) {
    Arete<Chemin, Case<Element>>* res = nullptr;

    Liste<Arete<Chemin, Case<Element>>>* tmp = game()->plateau()->aretesAdjacentes(monsterVertice);

    for(Liste<Arete<Chemin, Case<Element>>>* edges = tmp; edges; edges = edges->next) {
        double chaleur = edges->value->contenu().chaleur();
        if(chaleur > 0 && (!res || chaleur > res->contenu().chaleur())) {
            res = edges->value;
        }
    }

    Liste<Arete<Chemin, Case<Element>>>::efface1(tmp);

    if(res == nullptr) {
        throw NoHeatedEdgeFound("Aucune arête chaude trouvée");
    }

    if(monsterVertice == res->debut()) {
        return res->fin()->contenu().position();
    }
    else {
        return res->debut()->contenu().position();
    }
}
