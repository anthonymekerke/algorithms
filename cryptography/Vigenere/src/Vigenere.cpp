#include "Vigenere.hpp"

#include <iostream>
#include <fstream>
#include <array>

Vigenere::Vigenere() {}

Vigenere::~Vigenere() {}

void Vigenere::chiffrement(std::string cle, std::string filename){

    std::ifstream clearFile;
    std::ofstream cryptedFile;

    std::string stringToCrypt;
    std::string stringEncrypted;
    int indiceCle;

    clearFile.open(filename, std::ios::in);
    cryptedFile.open("../texts/texteChiffre.txt", std::ios::out);

    if(!clearFile.is_open()) { std::cout<<"erreur ouverture fichier!"<<std::endl; return; }

    clearFile >> stringToCrypt;
    indiceCle = 0;
    stringEncrypted.clear();
    while(!clearFile.eof()){

        for(int i = 0; i < stringToCrypt.length(); i++){
            if(stringToCrypt[i] >= 'A' && stringToCrypt[i] <= 'Z') {
                stringEncrypted.push_back((stringToCrypt[i] + cle[indiceCle] - 'A' - 'a') % 26 +'A');
            }
            else if(stringToCrypt[i] >= 'a' && stringToCrypt[i] <= 'z') {

            }

            if(indiceCle == (cle.length() - 1)) { indiceCle = 0; }
            else { indiceCle++; }
        }
        cryptedFile << stringEncrypted << " ";

        clearFile >> stringToCrypt;
        indiceCle = 0;
        stringEncrypted.clear();
    }

    clearFile.close();
    cryptedFile.close();
}

void Vigenere::dechiffrement(std::string cle, std::string filename){

    std::ifstream cryptedFile;
    std::ofstream clearFile;

    std::string stringToDecrypt;
    std::string stringDecrypted;
    int indiceCle;

    cryptedFile.open(filename, std::ios::in);
    clearFile.open("../texts/texteClair.txt", std::ios::out);

    if(!cryptedFile.is_open()) { std::cout<<"erreur ouverture fichier!"<<std::endl; return; }

    cryptedFile >>stringToDecrypt;
    indiceCle = 0;
    stringDecrypted.clear();
    while(!cryptedFile.eof()){

        for(int i = 0; i < stringToDecrypt.length(); i++){
            if(stringToDecrypt[i] >= 'A' && stringToDecrypt[i] <= 'Z') {
                stringDecrypted.push_back((stringToDecrypt[i] - cle[indiceCle] + 'a' - 'A' + 26) % 26 + 'A');
            }
            else if(stringToDecrypt[i] >= 'a' && stringToDecrypt[i] <= 'z') {
                stringDecrypted.push_back((stringToDecrypt[i] - cle[indiceCle] + 26) % 26 + 'a');
            }

            if(indiceCle == (cle.length()-1)) { indiceCle = 0; }
            else { indiceCle++; }
        }
        clearFile << stringDecrypted << " ";

        cryptedFile >>stringToDecrypt;
        indiceCle = 0;
        stringDecrypted.clear();
    }

    clearFile.close();
    cryptedFile.close();
}

float Vigenere::indiceCoincidence(std::string filename){
    std::array<int, 26> occurAlpha;
    std::ifstream cryptedFile;
    std::string stringToCut;
    float IC = 0.0f;
    int nbLettersTotal = 0;

    for(int k = 0; k < occurAlpha.size(); k++){ occurAlpha[k] = 0; }

    cryptedFile.open(filename, std::ios::in);

    while(!cryptedFile.eof()){
        cryptedFile>>stringToCut;

        for(int i = 0; i < stringToCut.length(); i++){
            if(stringToCut[i] >= 'A' && stringToCut[i] <= 'Z'){
                occurAlpha[stringToCut[i] - 'A']++;
                nbLettersTotal++;
            }
            else if (stringToCut[i] >= 'a' && stringToCut[i] <= 'z') {
                occurAlpha[stringToCut[i] - 'a']++;
                nbLettersTotal++;
            }
        }
    }

    cryptedFile.close();

    for(int i = 0; i < occurAlpha.size(); i++){
        IC += (occurAlpha[i] * (occurAlpha[i] - 1));
    }
    IC /= nbLettersTotal;
    IC /= (nbLettersTotal - 1);

    return IC;
}

float Vigenere::indiceCoincidenceK(std::string filename, int k){
    std::array<int, 26> occurAlpha;
    std::ifstream cryptedFile;
    float ICMax = 0;
    float IC;
    char c;

    cryptedFile.open(filename, std::ios::in);

    while(!cryptedFile.eof()){
        IC = 0.0f;

        for(int i = 0; i < occurAlpha.size(); i++){ occurAlpha[i] = 0; }

        for(int i = 0; i < k; i++) {
            cryptedFile >> c;

            if(c >= 'A' && c <= 'Z'){
                occurAlpha[c - 'A']++;
            }
            else if (c >= 'a' && c <= 'z') {
                occurAlpha[c - 'a']++;
            }
        }

        for(int i = 0; i < occurAlpha.size(); i++){
            IC += (occurAlpha[i] * (occurAlpha[i] - 1)) / (k * (k-1));
        }

        if(ICMax < IC) { ICMax = IC; }
    }
    cryptedFile.close();
    return ICMax;
}
