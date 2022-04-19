#ifndef KNAPSACK_ITERATEDLOCALSEARCH_HPP
#define KNAPSACK_ITERATEDLOCALSEARCH_HPP

#include "../localSearch/Search.hpp"
#include "../eval/evalFunc.hpp"

class IteratedLocalSearch : public Search {
private:
    evalFunc& _eval;
    Search& _localSearch;
    int _nbEval;

public:
    IteratedLocalSearch(evalFunc& eval, Search& ls, int nbEval);
};


#endif
