# TP3_Ingenierie_Modele

## Architecture 

Vous retrouverez dans ce projet 
- Un dossier **build** pour tous les fichiers .o générés à la compilation
- Un dossier **exe** pour les 2 executables
    - **question1** pour répondre à la question numéro 1
    - **subject** pour répondre aux autres question
- Un dossier **header** contenant les fichiers d'en-tête .hpp
- Un dossier **html** avec la documentation du programme au format .html
- Un dossier **main** contenant les 2 mains pour les 2 différents programmes
- Un dossier **src** pour les fichiers sources .cpp
- Un dossier **Random** pour la bibliothèque professionnelle de génération de nombres aléatoire
- Un fichier **cppcheck.txt** pour les améliorations possibles du code détecter par l'outil Cpp Check
- Un fichier **Dockerfile** pour la configuration de docker (optionnel)
- Un fichier **doxyfile** pour la configuration de la génération de la documentation
- Un fichier **Makefile** pour la génération des executables


## Le Makefile

Le Makefile permet de générer 2 executables comme énoncé précédemment. Quelques commandes utiles pour la génération des éxécutables. Toutefois, je vous conseille d'utiliser uniquement la dernière pour la génération du programme.

### Génération du code

- **make exe/question1** : Génération de l'executable pour la question 1
- **make exe/subject** : Génération de l'executable pour les autres questions

### Autres

- **make** : Affiche de l'aide pour l'utilisation des différentes commandes
- **make clean** : Nettoyer le repository
- **make check** : Lance l'outil Cpp Check pour améliorer le code.

## Outils 

### Markdown

Pour la création de ce README, j'ai utilisé l'extension de fichier .md. On peut par la suite exporter ceci sous format .pdf ou .html.

### Cpp Check

L'outil Cpp Check permet d'observer des warnings plus poussé et des améliorations possibles de notre code

### Docker

Docker permet de créer une image, et par la suite un container de mon projet. Il permet donc de connaître les caractéristiques de mon environment. L'application fonctionnera très bien sans installer Docker, je vous donne juste mon Dockerfile si vous voulez regarder.

### Doxygen

J'ai généré une documentation pour le programme avec l'outil doxygen. Pour la génération de la documentation, vous devez lancer la commande **doxygen doxyfile**. Sinon vous pouvez consulter directement le dossier html

## Le sujet

### Question 1 

Les bibliothèques CHLEF sont bien installées et insérées dans le dossier Random. Pour tester le bon fonctionnement de ce dernier, on utilise le main dans le fichier main/test.cc

### Question 2 

### Question 3 

### Question 4

### Question 5 

### Question 6

