# Chiffrement de Vigenere

## Utilisation

Le dossier ne dispose que d'un seul module appelé Vigenere.  
Il contient des méthodes de chiffrement, déchiffrement et cryptanalyse.  

Les fichiers textes à crypter/décrypter sont situés dans le dossier __texts/__.  

### Dépendances

[gcc](https://gcc.gnu.org/)

[Make](http://www.gnu.org/software/make/manual/make.html#Introduction)

[CMake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

### Installation / Compilation

```bash
cd cryptography
mkdir build/
cmake --build build/
```

### Lancement (run)

```bash
./main.out [arg] [cle] [filename]
arg: 
    -c -> Fonction de cryptage
    -d -> Fonction de decryptage
cle: chaîne de caractère
filename: Fichier à crypter/decrypter

./main.out [filename]
filename: Fichier à analyser (pas de clé fournie)
```
