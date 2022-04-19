# Knapsack

## Description

Ce programme implémente la résolution d'un problème d'optimisation combinatoire.

### Contexte

Module: Recherche Opérationnelle  
Master 1 WebScI, Université du Littoral Côte d'Opale  
Encadrant: Sebastien Verel, Professeur [page web](https://www-lisic.univ-littoral.fr/~verel/)  

### Énoncé

Un randonneur part un week-end en promenade. Au moment de préparer son sac se pose la question
des affaires à emporter. Son sac à dos étant limité en place, le randonneur se doit d'optimiser
la liste des affaires à prendre lors de son voyage.
Ainsi chacun de ses objets est définit par un gain (_profit) apporté par l'objet et un poids (_weight) que coûte l'objet.
L'objectif du randonneur est de maximiser le gain des objets emporté tout en minimisant le poids
de ceux-ci qui doit respecter la taille du sac à dos.

Ce projet est adapté du "problème du voyageur de commerce".

### Dérouler

Le programme principal charge le sac à dos (Classe 'Knapsack') à l'aide du fichier fournit en paramètre.  
Le fichier de configuration (ks_?.dat) est défini comme suit:  
\[Nombre d'objet\]  
\[Liste des gain (_profit)\]  
\[Liste des poids (_weight)\]  
\[Poids maximum du sac\]  
  
Une solution est ensuite instanciée à l'aide de la classe 'Solution'.  
Une solution consiste en un tableau de booléen ayant pour taille le nombre d'objet disponible et un indice de qualité (_fitness).  
Pour chaque objet disponible, le booléen correspondant défini si l'objet est pris dans la Solution ou non.  
La fitness correspond a la qualité de la Solution, elle est mesurée par la fonction d'évaluation.
  
La fonction d'évaluation est une interface implémentée par le Knapsack.  
Dans le cas présent, la fonction d'évaluation consiste en une somme pondéré des objets présents dans la Solution.  
  
L'objectif du programme étant de maximiser la fitness d'une Solution, plusieurs méthodes heuristiques 
et algorithmes de recherches local ont était implémentée:  

- RandomSearch

- RandomWalk

- HillClimber

- SimulatedAnnealing (= recuit simulé)

- IteratedLocalSearch

- EvolutionaryAlgorithm (= algorithme évolutionnaires)

### Algorithmes de recherche

#### RandomSearch

#### RandomWalk

#### HillClimber

#### Simulated Annealing

#### Iterated Local Search

#### Evolutionary Algorithm

## Utilisation

### Dépendances

### Installation / Compilation

``` bash
cd Knapsack
cmake build
cd build/
make ..
```

### Lancement (run)

``` bash

```

#### Help

"erreurs qui peuvent arriver, comment les résoudres"

### À savoir
