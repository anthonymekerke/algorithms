#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include "evalFunc.hpp"
#include "../base/Solution.hpp"

#include <vector>
#include <string>

struct Stuff{
    int _profit;
    int _weight;
};

class Knapsack : public evalFunc {
private:
    std::vector<Stuff> _sack;
    int _maxWeight;
    double _beta;

public:
    Knapsack(std::string filename);
    void print_sack();

    int profit(int i);
    int weight(int i);
    int size();

    virtual void eval(Solution& sol);

    ~Knapsack();
};

#endif
