#include "RSA.hpp"

#include <iostream>
#include <random>

int main(int argc, char** argv){

    char chiffre;
    char dechiffre;
    RSA rsa;

    srand(time(NULL));

    rsa.creationCle(5,7);
    chiffre = rsa.chiffrement('a');
    dechiffre = rsa.dechiffrement(chiffre);

    std::cout<<"chiffrement de a: "<<chiffre<<std::endl;
    std::cout<<"dechiffrement de "<<chiffre<<": "<<dechiffre<<std::endl;

    return 0;
}
