#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include<vector>

class Solution{
private:
    std::vector<bool> _x;
    double _fitness;

public:
    explicit Solution(int size);
    Solution(const Solution& s);

    double fitness() const;
    double& fitness();

    bool x(int i) const;
    void x(bool b, int i);

    int size() const;

    void print();

    Solution& operator=(const Solution& sol);
};

#endif
