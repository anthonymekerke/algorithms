#include "SDES.hpp"

#include <iostream>
#include <cmath>

SDES::SDES(std::string ci) {
    _CI.resize(ci.length());
    _K1.resize(ci.length());
    _K2.resize(ci.length());
    _ascii.resize(8);
    _working.resize(8);

    for(int i = 0; i < ci.length(); i++){
        if(ci[i] == '1') {_CI[i] = true; }
        else if(ci[i] == '0') {_CI[i] = false; }

    }
}

void SDES::printVector(std::vector<bool> v){
    for(unsigned i = 0; i < v.size(); i++){
        std::cout<<v[i]<<" ";
    }std::cout<<std::endl;
}

void SDES::cryptSDES(char c){
    asciiToOctet(c);

    std::cout<<"char "<<c<<": ";
    printVector(_ascii);

    for(unsigned i = 0; i < _ascii.size(); i++){
        _working[i] = _ascii[i];
    }

    findK1();
    std::cout<<"K1: ";
    printVector(_K1);

    findK2();
    std::cout<<"K2: ";
    printVector(_K2);

    permutationIP(_working);
    std::cout<<"working after IP: ";
    printVector(_working);

    fonctionFK(_working, _K1);
    std::cout<<"working after FK, K1: ";
    printVector(_working);

    permutationSW(_working);
    std::cout<<"working after SW: ";
    printVector(_working);

    fonctionFK(_working, _K2);
    std::cout<<"working after FK, K2: ";
    printVector(_working);

    permutationIPinverse(_working);
    std::cout<<"working after IPinverse: ";
    printVector(_working);
}

void SDES::fonctionF(std::vector<bool>& arg, std::vector<bool> KN){ //4 bits d'entrés, 4 bits de sortie
    std::cout<<"arg before fonction F: ";
    printVector(arg);

    expansionPermutation(arg);
    std::cout<<"arg after EP: ";
    printVector(arg);

    xorKN(arg,KN);
    std::cout<<"arg after xorKN: ";
    printVector(arg);

    sBox(arg);
    std::cout<<"arg after sBox: ";
    printVector(arg);

    permutationP4(arg);
    std::cout<<"arg after P4: ";
    printVector(arg);
}

void SDES::fonctionFK(std::vector<bool>& arg, std::vector<bool> KN) { //8 bits d'entrés, 4 bits les plus à gauche modifiés
    std::vector<bool> D;
    std::vector<bool> G;
    std::vector<bool> DIP;

    DIP = partieDroite(arg);
    D = partieDroite(arg);
    G = partieGauche(arg);

    fonctionF(D, KN);
    std::cout<<"arg after fonction F: ";
    printVector(D);

    xorPartieGauche(D, G);
    std::cout<<"arg after xor G: ";
    printVector(D);

    for(unsigned i = 0; i < arg.size(); i++){ //copie resultat FK dans arg

        if(i < arg.size()/2) { arg[i] = D[i]; }
        else { arg[i] = DIP[i - arg.size() / 2]; }
    }
}

void SDES::permutationSW(std::vector<bool>& v){ //8 bits d'entrés
    bool tmp;
    for(unsigned i = 0; i < v.size()/2; i++) {
        tmp = v[i];
        v[i] = v[i + v.size()/2];
        v[i + v.size()/2] = tmp;
    }
}

void SDES::permutationP10(std::vector<bool>& v){//10 bits d'entrés
    v[0] = _CI[2];
    v[1] = _CI[4];
    v[2] = _CI[1];
    v[3] = _CI[6];
    v[4] = _CI[3];
    v[5] = _CI[9];
    v[6] = _CI[0];
    v[7] = _CI[8];
    v[8] = _CI[7];
    v[9] = _CI[5];
}

void SDES::decalage(std::vector<bool>& v){ //10 bits d'entrés
    bool tmp;
    for(int i = 0; i < 10; i++) {
        if(i == 0 || i == 5) { tmp = v[i]; }
        if(i == 4 || i == 9) { v[i] = tmp; }
        else { v[i] = v[i + 1]; }
    }
}


void SDES::permutationP8(std::vector<bool>& v){//10 bits d'entrés, 8 bits de sortie
    v[0] = v[5];
    v[1] = v[2];
    v[2] = v[6];
    v[5] = v[4];
    v[4] = v[7];
    v[6] = v[9];
    v[7] = v[8];

    v.pop_back();
    v.pop_back();
}

void SDES::findK1(){
    permutationP10(_K1);
    decalage(_K1);
    permutationP8(_K1);
}

void SDES::findK2(){
    permutationP10(_K2);
    decalage(_K2);
    decalage(_K2);
    decalage(_K2);
    permutationP8(_K2);
}

void SDES::asciiToOctet(char c){
    for(int i = 7; i >= 0; i = i-1){
        if(c >= pow(2,i)){
            _ascii[7 - i] = true;
            c = (int)c % (int)pow(2,i);
        }
        else{ _ascii[7 - i] = false; }
    }
}

void SDES::permutationIP(std::vector<bool> &v){//8 bits d'entrés
    bool tmp0 = v[0];
    v[0] = v[1];
    v[1] = v[5];
    v[5] = v[7];
    v[7] = v[6];
    v[6] = v[4];
    v[4] = v[3];
    v[3] = tmp0;
}

void SDES::permutationIPinverse(std::vector<bool>& v){//8 bits d'entrés
    bool tmp5 = v[5];
    v[5] = v[1];
    v[1] = v[0];
    v[0] = v[3];
    v[3] = v[4];
    v[4] = v[6];
    v[6] = v[7];
    v[7] = tmp5;
}

std::vector<bool> SDES::partieGauche(std::vector<bool> v){ //8 bits d'entrés, 4 bits de sortie
    std::vector<bool> G;

    for(unsigned i = 0; i < v.size()/2; i++){ G.push_back(v[i]); }

    return G;
}

std::vector<bool> SDES::partieDroite(std::vector<bool> v){ //8 bits d'entrés, 4 bits de sortie
    std::vector<bool> D;

    for(unsigned i = v.size()/2; i < v.size(); i++){ D.push_back(v[i]); }

    return D;
}

void SDES::expansionPermutation(std::vector<bool>& v){ //4 bits d'entrés, 8 bits de sortie
    v.push_back(v[1]);
    v.push_back(v[2]);
    v.push_back(v[3]);
    v.push_back(v[0]);

    bool tmp2 = v[2];
    v[2] = v[1];
    v[1] = v[0];
    v[0] = v[3];
    v[3] = tmp2;
}

void SDES::xorKN(std::vector<bool>& v, std::vector<bool> KN){ //8 bits d'entrés, 8 bits de sortie
    for(unsigned i = 0; i < v.size(); i++){
        v[i] = v[i]^KN[i];
    }
}

void SDES::S0(std::vector<bool>& v){ //8 bits d'entrés, 4 modifiés
    int l = (int)v[0] * 2 + (int)v[3];
    int c = (int)v[1] * 2 + (int)v[2];

    if(l == 0 && c == 1 || l == 1 && c == 3 || l == 2 && c == 0){
        v[0] = 0;
        v[1] = 0;
    }
    if(l == 0 && c == 0 || l == 1 && c == 2 || l == 2 && c == 2 || l == 3 && c == 1){
        v[0] = 0;
        v[1] = 1;
    }
    if(l == 0 && c == 3 || l == 1 && c == 1 || l == 2 && c == 1 || l == 3 && c == 3){
        v[0] = 1;
        v[1] = 0;
    }
    if(l == 0 && c == 2 || l == 1 && c == 0 || l == 2 && c == 3 || l == 3 && c == 0 || l == 3 && c == 2){
        v[0] = 1;
        v[1] = 1;
    }
}

void SDES::S1(std::vector<bool>& v){ //8 bits d'entrés, 4 modifiés
    int l = (int)v[4] * 2 + (int)v[7];
    int c = (int)v[5] * 2 + (int)v[6];

    if(l == 0 && c == 0 || l == 1 && c == 1 || l == 2 && c == 1 || l == 2 && c == 3 || l == 3 && c == 2){
        v[2] = 0;
        v[3] = 0;
    }
    if(l == 0 && c == 1 || l == 1 && c == 2 || l == 2 && c == 2 || l == 3 && c == 1){
        v[2] = 0;
        v[3] = 1;
    }
    if(l == 0 && c == 2 || l == 1 && c == 0 || l == 3 && c == 0){
        v[2] = 1;
        v[3] = 0;
    }
    if(l == 0 && c == 3 || l == 1 && c == 3 || l == 2 && c == 0 || l == 3 && c == 3){
        v[2] = 1;
        v[3] = 1;
    }
}

void SDES::sBox(std::vector<bool>& v){ //8 bits d'entrés, 4 bits de sortie
    S0(v);
    S1(v);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
}

void SDES::permutationP4(std::vector<bool> &v){ //4 bits d'entrés, 4 bits de sortie
    bool tmp0 = v[0];
    v[0] = v[1];
    v[1] = v[3];
    v[3] = tmp0;
}

void SDES::xorPartieGauche(std::vector<bool>& v, std::vector<bool> G){ //4 bits d'entrés, 4 bits de sortie
    for(unsigned i = 0; i < v.size(); i++){
        v[i] = G[i]^v[i];
    }
}
