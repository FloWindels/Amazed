# 🤖 A-MAZE-D

**A-MAZE-D** est un projet de programmation en C réalisé dans le cadre du module B-CPE-200. L'objectif est de faire naviguer un ensemble de robots dans un labyrinthe, depuis une salle d'entrée jusqu'à une salle de sortie, en optimisant les déplacements.

## 📌 Objectif du projet

Développer un programme en C capable de :
- Lire et analyser un labyrinthe défini par un ensemble de salles et de tunnels.
- Vérifier la validité de la structure.
- Calculer les plus courts chemins disponibles pour chaque robot.
- Optimiser le passage des robots pour minimiser le nombre de tours ("laps").
- Générer une sortie conforme détaillant les mouvements de chaque robot.

## ⚙️ Compilation

Le projet se compile à l’aide d’un **Makefile** avec les règles suivantes :

- `make` : compile le binaire `amazed`
- `make clean` : supprime les fichiers objets
- `make fclean` : supprime les fichiers objets et le binaire
- `make re` : fclean + make

```bash
make
./amazed < labyrinth
```

## 📥 Format d'entrée

L’entrée est fournie via l’entrée standard et contient :

- Le nombre de robots à l’entrée
- La liste des salles avec leurs coordonnées
- Les tunnels reliant les salles
- Des lignes spéciales :
    - `##start` : indique que la prochaine salle est l’entrée
    - `##end` : indique que la prochaine salle est la sortie
    - `#` : ligne de commentaire

## Exemple

```bash
3

##start
0 1 0

##end
1 13 0

2 5 0
3 9 0

0-2
2-3
3-1
```

## 📤 Format de sortie

L'affichage sur la sortie standard doit inclure :

- Les informations d’entrée réaffichées
- Les déplacements par tour des robots sous forme Pn-r :
    - n : numéro du robot
    - r : nom de la salle atteinte

## Exemple de sortie

```bash
#number_of_robots
3
#rooms
...
#tunnels
...
#moves
P1-2
P1-3 P2-2
P1-1 P2-3 P3-2
P2-1 P3-3
P3-1
```

## 🧠 Fonctionnalités principales

- Parsing des entrées depuis stdin
- Vérification de validité du labyrinthe
- Représentation en graphe (matrice ou liste d’adjacence)
- Recherche de chemin (BFS / DFS / Dijkstra selon implémentation)
- Affichage conforme au format attendu


## 👥 Authors & Contributors

- [@FloWindels](https://github.com/FloWindels)
- [@llosts](https://github.com/llosts)
