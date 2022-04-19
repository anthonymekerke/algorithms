#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_

#include <vector>

#include "Solution.hpp"

class Population {
private:
    std::vector<Solution> _individuals;
    int _size;

public:
    Population(int size);

    int size() const;
    Solution individual(int i) const;
    void individual(int i, const Solution& sol);

    Population& operator=(const Population& pop);
};

#endif
