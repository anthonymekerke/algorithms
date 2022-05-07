#ifndef SDES_HPP_
#define SDES_HPP_

#include <vector>
#include <string>

class SDES{
public:
    std::vector<bool> _CI;
    std::vector<bool> _K1;
    std::vector<bool> _K2;

    std::vector<bool> _ascii;
    std::vector<bool> _working;

public:
    SDES(std::string ci);

    void printVector(std::vector<bool> v);
    void cryptSDES(char c);

private:
    void asciiToOctet(char c);

    void permutationP10(std::vector<bool>& v);
    void decalage(std::vector<bool>& v);
    void permutationP8(std::vector<bool>& v);

    void findK1();
    void findK2();

    void permutationIP(std::vector<bool>& v);
    void permutationIPinverse(std::vector<bool>& v);

    std::vector<bool> partieGauche(std::vector<bool> v);
    std::vector<bool> partieDroite(std::vector<bool> v);

    void expansionPermutation(std::vector<bool>& v);
    void xorKN(std::vector<bool>& v, std::vector<bool> KN);
    void sBox(std::vector<bool>& v);
    void S0(std::vector<bool>& v);
    void S1(std::vector<bool>& v);
    void permutationP4(std::vector<bool>& v);
    void xorPartieGauche(std::vector<bool>& v, std::vector<bool> G);

    void fonctionF(std::vector<bool>& arg, std::vector<bool> KN);
    void fonctionFK(std::vector<bool>& arg, std::vector<bool> KN);
    void permutationSW(std::vector<bool> &v);
};

#endif
