#ifndef _HILL_CLIMBER_HPP_
#define _HILL_CLIMBER_HPP_

#include "Search.hpp"
#include "../eval/evalFunc.hpp"

#include <random>

class HillClimber : public Search {
private:
    evalFunc& _eval;
    int _nbEval;
    int _improvement;

public:
    HillClimber(evalFunc& eval, int nbEval, int imp);
    void run(Solution &s);

    void runBestImprovement(Solution &s);
    void runFirstImprovement(Solution &s);

    void evaluate(Solution& s, int& evaluations);
};

#endif
