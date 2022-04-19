#ifndef _RANDOMWALK_HPP_
#define _RANDOMWALK_HPP_

#include "Search.hpp"
#include "../eval/evalFunc.hpp"

#include <vector>
#include <fstream>

class RandomWalk : public Search {
private:
    evalFunc& _eval;
    std::vector<double> _neighborhoodFitness;

public:
    explicit RandomWalk(evalFunc& eval);
    void run(Solution& s);
    void exportNeighborhoodToCsv() const;
};

#endif
