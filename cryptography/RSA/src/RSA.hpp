#ifndef _RSA_HPP_
#define _RSA_HPP_

class RSA {
private:
    int _n;
    int _phi;
    int _e;
    int _d;

public:

    RSA();
    void creationCle(int p, int q);
    int chiffrement(char c);
    int dechiffrement(char c);

private:
    int PGCD(int a, int b);
    int euclideEtendue(int a, int b);
};

#endif
