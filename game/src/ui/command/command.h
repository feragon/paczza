#pragma once

class Command {
    public:
        /**
         * @brief Exécute la commande
         */
        virtual void execute() = 0;
};