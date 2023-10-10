# containers
## Plan
#### 1 - Objectif du projet
#### 2 - Lancement du programme
#### 3 - Fonctionnement du programme
## 
### 1 - Objectif du projet
Containers fait partie des projets de l'école 42 et consiste à recoder les containers suivants en c++ :
- Vector
- Stack
- Map
- Set

Toutes les comportements des fonctions membres et non membres correspondent à ceux de la norme c++98 et sont disponible ici :
https://cplusplus.com/reference/stl/
https://en.cppreference.com/w/cpp/container

### 2 - Lancement du programme
La compilation peut se faire de deux façons :
1. Lancer la command ```make``` qui compilera le main de test. Qui est un main permettant de tester les comportement de toutes les fonctions des containers
2. Lancer le script 'launch_test.sh' qui compilera le main de test avec la library standard et avec notre library codée afin de comparer les outputs et vérifier que les comportements sont bien identiques. Ce script permet également de comparer les temps d'éxécution entre notre projet et la library standard.
```
make -j
```
L'exécution se fait en spécifiant le nom de la map à lancer en argument du programme, par exemple :
```
./cub3D ./maps/valid_maps/10_medium_map_sky_texture.cub
```
### 3 - Fonctionnement du programme
#### 3.1 - Lecture et formatage de la map
La map au format *.cub permet de définir les points suivants :
- les textures (fichiers *.xpm) utilisées pour les murs. La texture appliquée au mur diffère en fonction de son orientation nord, sud, est, ouest.
- la couleur du sol et du ciel avec un entier par couleur RGB.
- la map sur laquelle évolura le joueur. Les char utilisés pour definir la map sont :
  - 0 ou 1 pour indiquer un espace vide ou un mur
  - N, S, E ou W pour indiquer la position de départ du joueur. La lettre indique la direction vers laquelle le joueur regarde au lancement du jeu
- Voici un exemple de map utilisée :
```    
11111111
10000001
10001101
10E00001
11111111
```
Le programme final est capable de parser le fichier et détecter les cas d'erreurs possibles sur le fichier (informations manquantes, carte invalide...)
#### 3.2 - Gestion des textures
La MLX permet de convertir les images xpm en un format 'image' propre à la bibliothèque permettant une récupération facile de la couleur d'un pixel en fonction de sa position (x, y) dans l'image.
#### 3.3 - Raycasting
Pour représenter un monde en trois dimensions à partir d'une carte en deux dimensions un algorithme de raycasting est utilisé. La méthode consiste à balayer angulairement le champs de vision du joueur pour 'scanner' la carte en face de lui et déterminer la distance des murs.
Pour cela des rayons espacés angulairement sont créés (un rayon par colonne de pixel de la fenêtre de jeu). Pour une fenêtre de 1024 pixel par exemple, 1024 rayons seront créés. Pour chaque rayon partant du joueur, on calcule ensuite la distance du 1er mur impacté. L'algorithme de raycasting permet d'optimiser les calculs et maximiser les performances du jeu. Une fois la distance calculée, il est possible de connaître la hauteur du mur vu dans cette direction (inversement proportionnelle à la distance du mur) et ainsi dessiner le mur sur la fenêtre sur la colonne de pixel correspondante.
#### 3.4 - Mapping des texture
Pour mapper les texture, il suffit de connaître à quel pourcentage de hauteur et de largeur du mur le rayon a croisé le mur pour aller chercher dans la texture la couleur du pixel correspondant.
#### 3.5 - Gestion des évènements (hooks)
La MLX permet de gérer différents événements comme la pression des touches du clavier. Cela permet de changer la position du joueur et son orientation en fonction de la touche pressée.
#### 3.6 - Fin du programme
Le programme se termine si la map est invalide ou en cas d'exit demandé par le joueur. Avant de terminer l'execution, la mémoire allouée est libérée.
