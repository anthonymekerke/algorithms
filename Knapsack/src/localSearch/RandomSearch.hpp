#ifndef RANDOMSEARCH_HPP
#define RANDOMSEARCH_HPP

#include "Search.hpp"
#include "../eval/evalFunc.hpp"

class RandomSearch : public Search {
private:
    evalFunc& _eval;
    int _nbEval;

public:
    RandomSearch(evalFunc & eval, int nEvalMax);
    void run(Solution &s);
};

#endif
