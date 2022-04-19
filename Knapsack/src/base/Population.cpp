#include "Population.hpp"

Population::Population(int size) : _size(size) {
    _individuals.reserve(_size);
}

int Population::size() const { return _size; }

void Population::individual(int i, const Solution& sol) { _individuals[i] = sol; }

Solution Population::individual(int i) const {return _individuals[i]; }

Population& Population::operator=(const Population& pop) {
    for(int i = 0; i < _size; i++){
        _individuals[i] = pop.individual(i);
    }

    return *this;
}
