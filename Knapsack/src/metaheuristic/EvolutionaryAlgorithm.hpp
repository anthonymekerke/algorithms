#ifndef _EVOLUTIONARY_ALGORITHM_HPP_
#define _EVOLUTIONARY_ALGORITHM_HPP_

#include "../base/Population.hpp"
#include "../localSearch/Search.hpp"
#include "../eval/evalFunc.hpp"

class EvolutionaryAlgorithm : public Search {
/*private:
    evalFunc& _eval;
    int _mu;
    int _lambda;
    int _nbGen;

    Population _parents;
    Population _children;

public:
    EvolutionaryAlgorithm(evalFunc& eval, int mu, int lambda, int nbGen);

    void run(Solution &s);

    void init();
    void select();
    void evalPopulation(Population& pop);
    void variation();
    void replace();
    */
};

#endif
