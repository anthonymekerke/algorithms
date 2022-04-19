#include "RandomWalk.hpp"

RandomWalk::RandomWalk(evalFunc& eval) : _eval(eval) {}

void RandomWalk::run(Solution &s){
    Solution sprime(s);

    for(int i = 0; i < s.size(); i++){
        sprime.x(!s.x(i),i);
        _eval.eval(sprime);
        _neighborhoodFitness.push_back(sprime.fitness());
    }
}

void RandomWalk::exportNeighborhoodToCsv() const {
    std::ofstream file("../rw.csv");

    file<<"x \t fitness \n";

    for(unsigned i = 0; i < _neighborhoodFitness.size(); i++){
        file<<i+1<<"\t"<<_neighborhoodFitness[i]<<"\n";
    }
}
