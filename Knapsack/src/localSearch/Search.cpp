#include "Search.hpp"

#include <random>

void Search::buildRandomSolution(Solution &s) {
    int b;

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,1);

    for(int i = 0; i < s.size(); i++){
        b = distribution(engine);
        s.x((bool) b, i);
    }
    s.fitness() = 0;
}
