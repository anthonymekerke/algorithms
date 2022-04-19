#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP

#include "../localSearch/Search.hpp"
#include "../eval/evalFunc.hpp"

class SimulatedAnnealing : Search {
private:
    evalFunc& _eval;
    int _nbEval;
    int _temperature;
    float _alpha;

public:
    SimulatedAnnealing(evalFunc& eval, int nbEval, int temp, float alpha);
    void run(Solution &s);
    double initTemperature(Solution& s0, Solution& s0prime);
    void setRandomNeighbors(Solution& s, Solution& sprime);

};

#endif
