#include "SimulatedAnnealing.hpp"

#include <cstdlib>
#include <cmath>
#include <random>

SimulatedAnnealing::SimulatedAnnealing(evalFunc& eval, int nbEval, int temp, float alpha) :
    _eval(eval), _nbEval(nbEval), _temperature(temp), _alpha(alpha) {}

void SimulatedAnnealing::run(Solution &s){
    buildRandomSolution(s);
    Solution sprime(s.size());

    float temperature = _temperature;
    int notAccepted = 0;
    int nbEval = 0;
    int palier = 0;
    int delta;
    float u;

    while(nbEval < _nbEval) {
       setRandomNeighbors(s,sprime);

       _eval.eval(s);
       _eval.eval(sprime);
       nbEval++;
       palier++;

       delta = sprime.fitness() - s.fitness();

       if(delta > 0) { s = sprime; }
       else {
           u = 1.0f/ rand();

           if(u < exp(delta / temperature)) { s = sprime; }
           else { notAccepted++; }
       }

       if(palier == _nbEval / 100){
           palier = 0;
           temperature *= _alpha;
       }
    }
}

void SimulatedAnnealing::setRandomNeighbors(Solution& s, Solution& sprime) {
    int index;
    sprime = s;

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,s.size());

    index = distribution(engine);
    sprime.x(!s.x(index), index);
}

double SimulatedAnnealing::initTemperature(Solution& s0, Solution& s0prime) {
    double delta0 = 0;
    float tau0 = 0.5;
    int n = 10;

    for(int i = 0; i < n; i++){
        buildRandomSolution(s0);
        setRandomNeighbors(s0, s0prime);

        _eval.eval(s0);
        _eval.eval(s0prime);

        delta0 += s0.fitness() - s0prime.fitness();
    }
    delta0 /= n;

    return (log(tau0) / delta0);
}
