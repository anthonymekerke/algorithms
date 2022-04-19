cmake_minimum_required (VERSION 3.0)

project (Knapsack)

add_executable( main.out src/main.cpp
        src/eval/evalFunc.cpp
        src/eval/Knapsack.cpp
        src/base/Solution.cpp
        src/base/Population.cpp
        src/localSearch/Search.cpp
        src/localSearch/RandomSearch.cpp
        src/localSearch/RandomWalk.cpp
        src/localSearch/HillClimber.cpp
        src/metaheuristic/SimulatedAnnealing.cpp
        src/metaheuristic/EvolutionaryAlgorithm.cpp src/metaheuristic/IteratedLocalSearch.cpp src/metaheuristic/IteratedLocalSearch.hpp)

target_link_libraries( main.out )
