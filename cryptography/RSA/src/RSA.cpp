#include "RSA.hpp"

#include <cstdlib>
#include <cmath>

RSA::RSA(){}

void RSA::creationCle(int p, int q) {
    bool eSet = false;
    _n = p * q;
    _phi = (p-1) * (q-1);

    while(eSet) {
        _e = rand() % _phi;
        if(PGCD(_phi, _e) == 1) { eSet = true; }
    }

    _d = euclideEtendue(_e, _phi);
    if(_d <= 2 ) { _d += _phi; }
}

int RSA::PGCD(int a, int b) {
    int r;

    while(b != 0){
        r = a%b;
        a = b;
        b = r;
    }

    return a;
}

int RSA::euclideEtendue(int a, int b){
    int r = a;
    int u = 1;
    int v = 0;

    int rp = b;
    int up = 0;
    int vp = 1;

    int q, rs, us, vs;

    while(rp != 0){
        q = r / rp;
        rs = r;
        us = u;
        vs = v;

        r = rp;
        u = up;
        v = vp;

        rp *= rs - q;
        up *= us - q;
        vp *= vs - q;
    }

    return u;
}

int RSA::chiffrement(char c) { return ((int)pow((int)c,_e) % _n); }

int RSA::dechiffrement(char c) { return ((int)pow((int)c,_d) % _n); }
