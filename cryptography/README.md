# Initiation à la cryptographie

## Description

On souhaite implémenter différents algorithmes de cryptographie.

### Contexte

Module: Initiation à la cryptographie  
Master 1 WebScI, Université du Littoral Côte d'Opale  
Encadrant: Fabien Teytaud, Maître de conférence [page web](http://www-lisic.univ-littoral.fr/~teytaud/index.html)  

### Dérouler

Chaque algorithme de cryptographie dispose de son propre sous-dossier.  

#### Chiffrement de Vigenere

![image](img/matrice_vigenere.png "Matrice de Vigenere")

**Principe**: On dispose d'une matrice alphabétique et d'une clé que l'on choisie.  
Pour chaque lettre en clair, on sélectionne la colonne correspondante et pour une lettre de la clé on sélectionne la ligne adéquate, puis au croisement de la ligne et de la colonne on trouve la lettre chiffrée. La lettre de la clé est à prendre dans l'ordre dans laquelle elle se présente et on répète la clé en boucle autant que nécessaire.  

[Plus d\'infos](https://fr.wikipedia.org/wiki/Chiffre_de_Vigen%C3%A8re)  

#### Help

### À savoir
