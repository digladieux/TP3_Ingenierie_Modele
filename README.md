# TP3_Ingenierie_Modele

## Architecture 

Vous retrouverez dans ce projet 
- Un dossier **build** pour tous les fichiers .o générés à la compilation, les fichiers CMake, les executables
    - **question1** pour répondre à la question numéro 1
    - **subject** pour répondre aux autres question
- Un dossier **header** contenant les fichiers d'en-tête .hpp
- Un dossier **html** avec la documentation du programme au format .html
- Un dossier **main** contenant les 2 mains pour les 2 différents programmes
- Un dossier **Numbers** pour les nombres de MT sauvegardés
- Un dossier **src** pour les fichiers sources .cpp
- Un dossier **Status** pour les status de MT sauvegardé
- Un dossier **Random** pour la bibliothèque professionnelle de génération de nombres aléatoire
- Un fichier **Dockerfile** pour la configuration de docker (optionnel)
- Un fichier **doxyfile** pour la configuration de la génération de la documentation

## Le CMake

Le CMakeLists.txt permet de générer 2 executables comme énoncé précédemment. Il faut créer le dossier **build**, aller dedans et ensuite  lancer les commandes

- **cmake ..** : Génération du makefile
- **make** : Génération des 2 executables + utilisation de cpp check
- **make clean** : Nettoyer le repository

## Outils 

### Markdown

Pour la création de ce README, j'ai utilisé l'extension de fichier .md. On peut par la suite exporter ceci sous format .pdf ou .html.

### Cpp Check
    
L'outil Cpp Check permet d'observer des warnings plus poussé et des améliorations possibles de notre code. Il est lancé a chaque fois lors du `make`

### Docker

Docker permet de créer une image, et par la suite un container de mon projet. Il permet donc de connaître les caractéristiques de mon environment. L'application fonctionnera très bien sans installer Docker, je vous donne juste mon Dockerfile si vous voulez regarder.

### Doxygen

J'ai généré une documentation pour le programme avec l'outil doxygen. Pour la génération de la documentation, vous devez lancer la commande **doxygen doxyfile**. Sinon vous pouvez consulter directement le dossier html

## Le sujet

### Question 1 

Les bibliothèques CHLEF sont bien installées et insérées dans le dossier Random. Pour tester le bon fonctionnement de ce dernier, on execute l'executable question1

### Question 2 et 3

Elle est séparé en plusieurs points.
1°) On génère 10 status de 10 nombres
2°) On verifie que les status sont bien restauré (ce qui reprend la question 3)
3°) On lance 10 réplication de MonteCarlo avec 10 nombres. Les résultats sont mauvais ce qui est normal

### Question 4

On genere 10 status de 2 milliards de nombres (car 1 Milliards de points pour Monte Carlo).
Ensuite on lance en séquentiel 10 experiences de Monte Carlo

### Question 5.A

On sépare la question en 3 parties
1°) On genere le mot **gattaca**, avec le dictionnaire **acgt**. On donne des statistiques pour 40 essais
2°) Calcul de la probabilité pour avoir la phrase **Le hasard n'est pas un programme.**
3°) Calcul de la probabilité pour avoir un ADN parmis les 3 milliards de bases

### Question 5.B

On fait la même operation qu'a la question 4. En revanche on passe du séquentiel aux threads. On remarque qu'on a les résultats des 10 expériences en même temps, ce qui est un gain de temps énorme
