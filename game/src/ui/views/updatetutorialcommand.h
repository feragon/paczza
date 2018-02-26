#pragma once

#include <ui/command/command.h>
#include "tutorialview.h"

class UpdateTutorialCommand : public Command {
    public:
        /**
         * @brief Crée une commande qui affiche le prochain message du tutoriel
         * @param view Vue du tutoriel
         */
        UpdateTutorialCommand(TutorialView* view);

        virtual void execute() override;

    private:
        TutorialView* _view;
};