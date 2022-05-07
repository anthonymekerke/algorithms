#ifndef _VIGENERE_HPP_
#define _VIGENERE_HPP_

#include <string>

class Vigenere{

public:
    Vigenere();
    ~Vigenere();

    void chiffrement(std::string cle, std::string filename);
    void dechiffrement(std::string cle, std::string filename);

    float indiceCoincidence(std::string filename);
    float indiceCoincidenceK(std::string filename, int k);
};

#endif
