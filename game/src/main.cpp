#include <ui/fenetrejeu.h>

int main() {
    try {
        FenetreJeu fenetre;
        fenetre.ouvrir();

        return EXIT_SUCCESS;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
