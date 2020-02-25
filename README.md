---
title: "Projet Architecture des Machines et des Systèmes"
subtitle: "Client/Serveur"
author:
  - Sacha FROMENT
  - Sivaajithan SIVATHEVAN
lang: fr
---

## Contexte du projet

L'objectif de ce projet est de mettre en oeuvre un système de processus
clients/serveurs permettant d'offrirs des services aux utilisateurs.

Afin de mettre en place ce système, une des contraintes est d'utiliser les
systèmes de communication inter-processus disponibles au sein des systèmes UNIX.
Notamment les tubes nommés(ou non), les files de messages ou encore les
sémaphores.

Il est également important de prendre en compte la performance des différentes
services proposés à l'aide des méchanismes des fork et threads.

On informera l'utilisateur à la suite de l'exécution de son service des
ressources utilisés nécessaires au calcul de celui ci. Pour cela on utilisera le
système de fichiers virtuel /proc. Il rend possible l'accès à différentes
informations sur le système et les processus en cours.

## Compilation et exécution

Afin de compiler le projet, il suffit d'exécuter dans le repertoire la
commande :

```bash
make clean all
```

cela génerera deux executables nommés `serveur` et `client` dans le repertoire
`bin/`.
Ensuite il est necessaire de démarrer le serveur en faisant :

```bash
./bin/serveur
```

Une fois cela fait, on peut démarrer lancer des clients afin de demander
l'execution des différents services.  
Pour cela il est possible de saisir les commandes suivantes :

- Listage des services disponibles :

  ```bash
  ./bin/client services
  ```

- Calcul simple

  ```bash
  ./bin/client calcul-simple + 5 3.14 6 [...]
  ./bin/client calcul-simple - 8 4 2 [...]
  ./bin/client calcul-simple "*" 6.25 35  [...] ( ou calcul-simple \* [...] )
  ./bin/client calcul-simple / 2 3.25 [...]
  ./bin/client calcul-simple "**" 2 6 [...]
  ```

- Compteur de caractères

  ```bash
  ./bin/client compteur-char text ceci est une phrase
  ./bin/client compteur-char text "une phrase" "voici autre une phrase"
  ./bin/client compteur-char file ./ceci_est_un_fic.txt
  ./bin/client compteur-char file "./ceci_est_un_fic.txt"
  ./bin/client compteur-char file "/home/user/fic.txt"
  ```

- Compteur de mots

  ```bash
  ./bin/client compteur-mots text ceci est une phrase
  ./bin/client compteur-mots text "une phrase" "voici une autre phrase"
  ./bin/client compteur-mots file ./ceci_est_un_fic.txt
  ./bin/client compteur-mots file "./ceci_est_un_fic.txt"
  ./bin/client compteur-mots file "/home/user/fic.txt"
  ```

- Probabilité qu'un caractère suive une autre caractère

  ```bash
  ./bin/client proba-char text ceci est une phrase
  ./bin/client proba-char text "une phrase" "voici une autre phrase"
  ./bin/client proba-char file ./ceci_est_un_fic.txt
  ./bin/client proba-char file "./ceci_est_un_fic.txt"
  ./bin/client proba-char file "/home/user/fic.txt"
  ```

- Probabilité qu'un mot suive une autre mot

  ```bash
  ./bin/client proba-mots text ceci est une phrase
  ./bin/client proba-mots text "une phrase" "voici une autre phrase"
  ./bin/client proba-mots file ./ceci_est_un_fic.txt
  ./bin/client proba-mots file "./ceci_est_un_fic.txt"
  ./bin/client proba-mots file "/home/user/fic.txt"
  ```

  Le résultat s'affiche sur la **sortie standard**.

## Script de test

Un petit script de test à été écrit.  
par défaut il lance 100 clients :

```bash
./test.sh
```

Il accepte en paramètre un nombre arbitraire de clients à lancer :

```bash
./test.sh 10000
```

lance 10000 clients
