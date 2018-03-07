#pragma once

#include <ui/command/command.h>
#include "credits.h"

class UpdateCreditSpeed : public Command {
    public:
        /**
         * @brief Crée une commande qui change la vitesse de défilement des crédits
         * @param credits Vue des crédits
         * @param speed Nouvelle vitesse de défilement
         */
        UpdateCreditSpeed(Credits* credits, int speed);

        virtual void execute() override;

    private:
        Credits* _credits;
        int _speed;
};