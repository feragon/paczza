#include "updatecreditspeed.h"

UpdateCreditSpeed::UpdateCreditSpeed(Credits* credits, int speed) {
    _credits = credits;
    _speed = speed;
}

void UpdateCreditSpeed::execute() {
    _credits->setSpeed(_speed);
}