#include "HillClimber.hpp"

HillClimber::HillClimber(evalFunc &eval, int nbEval, int imp) : _eval(eval), _nbEval(nbEval), _improvement(imp) {}


void HillClimber::run(Solution &s){
    if(_improvement == 0) { runBestImprovement(s); }
    else { runFirstImprovement(s); }
}

void HillClimber::evaluate(Solution &s, int& evaluations) {
    _eval.eval(s);
    evaluations++;
}

void HillClimber::runBestImprovement(Solution& s) {
    Solution sprime(s.size());
    Solution currentNeighbor(s.size());

    int nbeval = 0;
    bool localOptimum = false;

    buildRandomSolution(s);
    evaluate(s,nbeval);

    while(nbeval < _nbEval && !localOptimum){
        sprime = s;
        currentNeighbor = sprime;

        for(int i = 0; i < s.size(); i++) { //find the best neighbor of sprime
            currentNeighbor.x(!currentNeighbor.x(i), i);
            evaluate(currentNeighbor,nbeval);

            if(sprime.fitness() <= currentNeighbor.fitness()) { sprime = currentNeighbor; }

            currentNeighbor.x(!currentNeighbor.x(i), i);
        }

        if(s.fitness() < sprime.fitness()) { s = sprime; }
        else if(s.fitness() == sprime.fitness() ) { localOptimum = true; }
    }
}

void HillClimber::runFirstImprovement(Solution &s) {
    Solution sprime(s);

    int index;
    int nbeval = 0;
    int nbNeighbor = 0;
    bool localOptimum = false;

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,s.size());

    buildRandomSolution(s);
    evaluate(s,nbeval);

    while(nbeval < _nbEval && !localOptimum){
        index = distribution(engine);
        sprime.x(!sprime.x(index),index);
        nbNeighbor++;

        evaluate(sprime,nbeval);

        while(sprime.fitness() < s.fitness() && nbeval < _nbEval && nbNeighbor < s.size()) {
            index = distribution(engine);
            sprime.x(!sprime.x(index),index);
            evaluate(sprime,nbeval);
        }

        if(s.fitness() < sprime.fitness()) { s = sprime; }
        else if(s.fitness() == sprime.fitness() ) { localOptimum = true; }
    }
}