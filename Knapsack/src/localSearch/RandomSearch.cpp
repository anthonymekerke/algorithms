#include "RandomSearch.hpp"

RandomSearch::RandomSearch(evalFunc& eval, int nEvalMax) : _eval(eval), _nbEval(nEvalMax) {}

void RandomSearch::run(Solution& s){
    Solution best(s);

    for(int i = 0; i < _nbEval; i++){
        buildRandomSolution(s);
        _eval.eval(s);

        if(s.fitness() > best.fitness()) { best = s; }
    }

    s = best;
}
