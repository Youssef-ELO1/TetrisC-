Tetris - Projet en C++ avec Qt Creator

Bienvenue dans notre projet Tetris, une implémentation moderne du jeu classique en C++20, utilisant Qt Creator pour l'interface utilisateur.
Prérequis

Avant de commencer, assurez-vous d'avoir installé les éléments suivants :

    Qt Creator pour l'interface utilisateur avec une version Qt Creator 11.0.2 et Fondé sur Qt 6.4.3.
    Un compilateur supportant le C++20.
    CMake pour la gestion de la construction du projet.

Structure du projet

Le projet est structuré comme suit :

Tetris_56065_56117_Gui/
    ├── CMakeLists.txt
    └── ... (autres fichiers sources et headers)

Configuration

    Cloner le dépôt :

    git clone https://git.esi-bru.be/56065/tetris_56065_56117.git
    cd Tetris_56065_56117_Gui

Préparation de l'environnement :
Avant de commencer à travailler avec le projet dans Qt Creator, assurez-vous de supprimer tout fichier nommé CMakeLists.txt.user. 
Ces fichiers peuvent contenir des configurations spécifiques à l'utilisateur qui peuvent induire en erreur et empêcher l'application de se lancer correctement.

Compilation

Pour compiler le projet, suivez ces étapes :

    Ouvrir Qt Creator et charger le projet :
        Lancez Qt Creator.
        Sélectionnez File > Open File or Project....
        Naviguez jusqu'au dossier tetris_56065_56117\Tetris_56065_56117-gui et ouvrez le fichier CMakeLists.txt.

    Configurer le projet :
        Assurez-vous que Qt Creator utilise un kit compatible avec le C++20.
        Configurez le chemin de construction si nécessaire.

    Build le projet :
        Cliquez sur Build > Build Project "Tetris".

Exécution

Après la compilation, vous pouvez exécuter le projet directement depuis Qt Creator en cliquant sur Run