# Travail pratique 1 : Génération d'une grille de tournoi

## Description

Ce projet a pour objectif d'organiser un tournoi à partir d'une liste de joueurs.
Un fichier contenant le nom des joueurs est donné en entrée, et le programme
génère ensuite une grille sur la sortie standard, indiquant l'ordre des matchs.

Le type du tournoi utilisé dans ce projet est le tournoi à la ronde.
Vous pouvez en apprendre plus sur cette [page 
Wikipédia.](https://fr.wikipedia.org/wiki/Tournoi_toutes_rondes)

Pour que le programme fonctionne correctement, le nombre minimal de joueurs
est de deux (2), alors que le nombre maximal est de vingt (20).

Le projet est accompli dans le cadre du cours de Construction et maintenance
de logiciels (INF3135) de l'Université du Québec à Montréal (UQAM).
Le professeur Guy Francoeur enseigne ce cours pour la session d'automne 2019.
Il s'occupe du groupe 40 dans lequel se retrouve l'auteur de ce projet.

Voici un lien vers l'[énoncé du
travail.](https://gitlab.info.uqam.ca/inf3135-aut2019/inf3135-aut2019-tp1-enonce)

## Auteur

Xavier Dupré (DUPX28029808)

## Fonctionnement

Pour compiler le programme, exécuter la commande suivante.
```
$ make tournament
```
Cette commande permet de créer l'exécutable *tournament* dans le dossier.
Il faut s'assurer que le fichier *Makefile* existe aussi dans le dossier.

Pour ensuite exécuter le programme, entrer la commande suivante.
```
$ ./tournament < exemple.in
```
Le fichier *exemple.in* doit contenir la liste des joueurs.
La grille du tournoi est ensuite affichée sur la sortie standard.

L'option *-f* ou *--format* permet d'ajuster le format de la grille du tournoi.
La valeur *id* affiche l'identifiant du joueur dans la grille, soit son nombre.
La valeur *name* affiche, quant à elle, le nom du joueur dans la grille.
Voici quelques exemples.
```
$ ./tournament -f id < exemple.in
$ ./tournament --format name < exemple.in
```

L'option *-s* ou *--style* permet d'ajuster le style de la grille du tournoi.
La valeur *compact* et la valeur *table* sont les deux choix disponibles.
Voici quelques exemples.
```
$ ./tournament -s compact < exemple.in
$ ./tournament --style table < exemple.in
```

## Tests

Pour lancer la suite de tests automatiques, entrer la commande suivante.
```
$ make test
```
L'état de chaque test sera affiché sur la sortie standard.
Le nombre de tests réussis et de tests échoués seront aussi affichés.

## Dépendances

* GCC;
* [Bats](https://github.com/sstephenson/bats).

## Références

* [Tournoi toutes rondes](https://fr.wikipedia.org/wiki/Tournoi_toutes_rondes);
* [Table de Berger](https://fr.wikipedia.org/wiki/Table_de_Berger).

## État du projet

* [x] Le nom du dépôt GitLab est exactement `inf3135-aut2019-tp1` (Pénalité de
  **50%**).
* [x] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.info.uqam.ca/utilisateur/inf3135-aut2019-tp1`
  (Pénalité de **50%**).
* [x] L'utilisateur `blondin_al` (groupe 20) ou `francoeur_g` (groupe 40)
  a accès au projet en mode *Developer* (Pénalité de **50%**).
* [x] Le dépôt GitLab est un **clone** de [ce
  dépôt](https://gitlab.info.uqam.ca/inf3135-aut2019/inf3135-aut2019-tp1)
  (Pénalité de **50%**).
* [x] Le dépôt GitLab est privé (Pénalité de **50%**).
* [x] Le dépôt contient au moins un fichier `.gitignore`.
* [x] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `test` et `clean`.
* [x] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué.
* [x] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [x] L'en-tête du fichier est documentée.
* [x] L'en-tête des prototypes des fonctions est documentée (*docstring*).
* [x] Le programme ne contient pas de valeurs magiques.
