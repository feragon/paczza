#include "sensemonstermanager.h"
#include "playernotinsight.h"
#include "noheatededgefound.h"
#include "dumbmonstermanager.h"
#include <game/jeu.h>

SenseMonsterManager::SenseMonsterManager(Jeu* game) :
        MonsterManager(game) {
    srand(time(NULL));
}

void SenseMonsterManager::moveMonsters(const Position<>& playerPosition) {
    monsters().clear();
    for(Liste<Monster>* monster = game()->monsters(); monster; monster = monster->next) {
        Sommet<Case>* monsterVertice = game()->plateau()->sommet(monster->value->position()->contenu().position());
        try {
            monsters()[monster->value] = nextPositionBySight(monsterVertice, playerPosition);
        }
        catch (PlayerNotInSight& e) {
            try {
                monsters()[monster->value] = nextPositionByHeat(monsterVertice);
            }
            catch (NoHeatedEdgeFound& f) {
                monsters()[monster->value] = DumbMonsterManager::getNextPosition(game()->plateau(), monsterVertice);
            }
        }
    }
}

Position<> SenseMonsterManager::nextPositionBySight(const Sommet<Case>* monsterVertice, const Position<>& playerPosition) {
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
    Liste<Sommet<Case>>* tmp = game()->plateau()->voisins(monsterVertice);
    Liste<Sommet<Case>>* neighbors = tmp;
    while(neighbors) {
        if(neighbors->value->contenu().position() == next) {
            if(next == playerPosition) {
                Liste<Sommet<Case>>::efface1(tmp);
                return monsterPosition + direction;
            }
            else {
                next = next + direction;
                neighbors = game()->plateau()->voisins(neighbors->value);
                Liste<Sommet<Case>>::efface1(tmp);
                tmp = neighbors;
            }
        }
        else {
            neighbors = neighbors->next;
        }
    }

    Liste<Sommet<Case>>::efface1(tmp);
    throw PlayerNotInSight("Il n'y a pas de chemin entre le monstre et le joueur");
}

Position<> SenseMonsterManager::nextPositionByHeat(const Sommet<Case>* monsterVertice) {
    Arete<Chemin, Case>* res = nullptr;

    Liste<Arete<Chemin, Case>>* tmp = game()->plateau()->aretesAdjacentes(monsterVertice);

    for(Liste<Arete<Chemin, Case>>* edges = tmp; edges; edges = edges->next) {
        double chaleur = edges->value->contenu().chaleur();
        if(chaleur > 0 && (!res || chaleur > res->contenu().chaleur())) {
            res = edges->value;
        }
    }

    Liste<Arete<Chemin, Case>>::efface1(tmp);

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
