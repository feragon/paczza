# Pac-Zza

Mort aux ananas !

# Ressources utilisées
- Police de caractères Kongtext par codeman38
- Police de caractères DoCoMo par Monica Dinculescu

# Execution
L'exécutable doit être exécuté dans le dossier où se trouve le dossier `res`  

# Compilation sur Linux
```commandline
mkdir build
cd build
cmake ..
make
./game/paczza
```

# Compilation sur Windows
- Ouvrir CMake GUI
- Mettre la racine du dépôt comme source
- Créer un dossier build pour générer le projet
- Cliquer sur Configure et mettre la bonne version du compilateur
- Créer une entrée _SFML_ROOT_ de type _PATH_, en mettant le dossier racine de SFML (qui contient includes et lib)
- Cliquer sur Generate

## Utilisation de Visual Studio
- Clic droit sur le projet _paczza_ > propriétés
- Aller dans C/C++, Ligne de commande
- Ajouter `/utf-8`