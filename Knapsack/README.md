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
la liste des objets à prendre lors de son voyage.
Ainsi chaque objet est définit par un gain (_profit_) et un poids (_weight_).
L'objectif du randonneur est de maximiser le gain des objets emporté tout en minimisant le poids
de ceux-ci qui doit respecter la taille du sac à dos.

Ce projet est adapté du ["problème du sac à dos"](https://fr.wikipedia.org/wiki/Probl%C3%A8me_du_sac_%C3%A0_dos).

### Dérouler

Le programme principal charge le sac à dos (_Classe 'Knapsack'_) à l'aide du fichier fournit en paramètre.  
Le fichier de configuration (**ks_?.dat**) est formaté comme suit:  
<div align="center">
<p>[Nombre d'objet]</p>  
<p>[Liste des gains <i>(profit)</i>]</p>  
<p>[Liste des poids <i>(weight)</i>]</p>
<p>[Poids maximum du sac]</p>  
</div>
  
Une solution est ensuite instanciée à l'aide de la classe _'Solution'_.  
Une solution consiste en un tableau de booléen ayant pour taille le nombre d'objet disponible et un indice de qualité (_fitness_).  
Pour chaque objet disponible, le booléen correspondant défini si l'objet est pris dans la Solution ou non.  
La fitness correspond a la qualité de la Solution, elle est mesurée par la fonction d'évaluation.
  
La fonction d'évaluation est une interface implémentée par le Knapsack.  
Dans le cas présent, la fonction d'évaluation consiste en une somme pondéré des objets présents dans la Solution.  
  
L'objectif du programme étant de maximiser la fitness d'une Solution, plusieurs méthodes heuristiques 
et algorithmes de recherches local ont était implémenté:  

- RandomSearch

- RandomWalk

- HillClimber

- SimulatedAnnealing (= recuit simulé)

- IteratedLocalSearch

- EvolutionaryAlgorithm (= algorithme évolutionnaires)

### Algorithmes de recherches

#### RandomSearch

**Principe:** À chaque itération de l'algorithme, une nouvelle solution aléatoire est généré. Si la
qualité (_fitness_) est meilleurs que la Solution sauvegardé, on la remplace.  
[Plus d'infos](https://en.wikipedia.org/wiki/Random_search)  

#### RandomWalk

**Principe:** On utilise cet algorithme afin d'avoir une idée du voisinage d'une Solution.

[Plus d'infos](https://en.wikipedia.org/wiki/Random_walk)

#### HillClimber

**Principe:** L'objectif est de trouver un optimum local.  
On génère une Solution aléatoire. À chaque itération de l'algorithme on sélectionne
une Solution dans le voisinage de la Solution sauvegardé. Si la qualité (_fitness_) est meilleur, on
la remplace. Dans le cas présent, le voisinage d'une Solution est définie tel que l'ensemble des
booléen qui la compose sont similaires sauf un choisie au hasard ([Distance de Hamming](https://fr.wikipedia.org/wiki/Distance_de_Hamming)).  
[Plus d'infos](https://en.wikipedia.org/wiki/Hill_climbing)

#### Simulated Annealing

**Principe:** L'objectif est d'éviter les optimum locaux.  
À chaque itération de l'algorithme deux choix sont possibles:

- On sélectionne une Solution S' dans le voisinage de S avec une meilleur qualité (_fitness_)

- On accepte une Solution qui dégrade la qualité actuel afin d'explorer l'espace de recherche

[Plus d'infos](https://en.wikipedia.org/wiki/Simulated_annealing)

#### Iterated Local Search

**Principe:** Lorsqu'on effectue une Recherche Local on peut se retrouver bloqué par un
optimum/minimum local. Dans ce cas on "perturbe" la Solution courante pour initier
une nouvelle recherche à partir de celle-ci.  
[Plus d'infos](https://en.wikipedia.org/wiki/Iterated_local_search)

#### Evolutionary Algorithm

**Principe:** C'est un algorithme "calqué" sur la sélection naturelle.  
On manipule une Population de Solution initialisé aléatoirement, puis on réitère différentes étapes:

- On évalue la qualité de l'ensemble des Solutions de la Population

- On sélectionne les meilleurs Solutions qui deviennent Parents

- À partir des Solutions Parents, on génère une nouvelle Population Enfant

- On effectue une mutation sur certains individus de la Population

- On réitère ces étapes un certains nombre de fois

Chaque étape de l'algorithme évolutionnaire est appelé une "Generation", le nombre de generation
est définie au préalable.

[Plus d'infos](https://en.wikipedia.org/wiki/Evolutionary_algorithm)

## Utilisation

### Dépendances

### Installation / Compilation

``` bash
cd Knapsack
mkdir build
cd build/
cmake ..
cmake --build .
```

### Lancement (run)

``` bash
./main.out [filename] [algorithm]

filename:
../ks_5.dat
../ks_1000.dat

algorithm:
-rs -> -rs [nbEval]
-rw -> -rw
-hc -> -hc [nbEval] [improvement: 0=best, 1=first]
-sa -> -sa [nbEval] [initTemperature] [alpha]
```

#### Help

"erreurs qui peuvent arriver, comment les résoudres"

### À savoir
