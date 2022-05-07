#include "Vigenere.hpp"

#include <iostream>

int main(int argc, char** argv){

    Vigenere v;
    float IC = 0.0f;

    if( (std::string)argv[1] == "-c") { v.chiffrement(argv[2], argv[3]); }
    else if( (std::string)argv[1] == "-d") { v.dechiffrement(argv[2], argv[3]); }
    else { std::cout<<"erreur d'option, choississez -c ou -d"<<std::endl; }

    IC = v.indiceCoincidence(argv[2]);

    std::cout<<"indice de coincidence: "<<v.indiceCoincidence(argv[2])<<std::endl;

    for(int i = 2; i < 12; i++){
        std::cout<<"k = "<<i<<", IC: "<<v.indiceCoincidenceK(argv[2],i)<<std::endl;
    }




    return 0;
}
