#include "Solution.hpp"

#include<iostream>

Solution::Solution(int size) : _fitness(0) {
    _x.resize(size);
}

Solution::Solution(const Solution &s) : _fitness(s.fitness()) {
    for(int i = 0; i < s.size(); i++){
        _x.push_back(s.x(i));
    }
}

double Solution::fitness() const {return _fitness; }
double& Solution::fitness() {return _fitness; }

bool Solution::x(int i) const { return _x[i]; }
void Solution::x(bool b, int i) { _x[i] = b; }

void Solution::print(){

    for(int i = 0; i < _x.size(); i++){
        std::cout<<"_x["<<i<<"]: "<<_x[i]<<std::endl;
    }

    std::cout<<"fitness: "<<_fitness<<std::endl;
}

int Solution::size() const {return (int)_x.size(); }

Solution& Solution::operator =(const Solution& sol){

    _fitness = sol.fitness();
    _x.resize(sol.size());

    for(int i = 0; i < sol.size(); i++){ _x[i] = sol.x(i); }

    return *this;
}
