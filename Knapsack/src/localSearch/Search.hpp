#ifndef LOCALSEARCH_HPP_
#define LOCALSEARCH_HPP_

#include "../base/Solution.hpp"

class Search {
public:
    virtual void run(Solution& s) =0;
    void buildRandomSolution(Solution& s);
};

#endif
