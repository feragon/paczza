#include "util.h"

Direction getDirection(const Position<>& depart, const Position<>& fin) {
    Position<> diff = fin - depart;

    if(diff.x == 0) {
        if(diff.y > 0) {
            return DOWN;
        }
        else if(diff.y < 0) {
            return UP;
        }
        else {
            throw std::runtime_error("Direction invalide");
        }
    }
    else if(diff.x > 0) {
        if(diff.y > 0) {
            return RIGHT_DOWN;
        }
        else if(diff.y < 0) {
            return RIGHT_UP;
        }
        else {
            return RIGHT;
        }
    }
    else {
        if(diff.y > 0) {
            return LEFT_DOWN;
        }
        else if(diff.y < 0) {
            return LEFT_UP;
        }
        else {
            return LEFT;
        }
    }
}
