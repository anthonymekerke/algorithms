#include <iostream>

#include "eval/Knapsack.hpp"
#include "base/Solution.hpp"
#include "localSearch/RandomSearch.hpp"
#include "localSearch/RandomWalk.hpp"
#include "localSearch/HillClimber.hpp"
#include "metaheuristic/SimulatedAnnealing.hpp"

int main(int argc, char** argv){

    Knapsack ks(argv[1]);
    Solution sol(ks.size());

    //RandomSearch
    if(std::string(argv[2]) == "-rs") {
        if(argc == 4) {
            RandomSearch rs(ks, std::stoi(argv[3]));
            rs.run(sol);
            sol.print();
            std::cout << argv[3] << "\t" << sol.fitness() << std::endl;
        }
        else { std::cout<<"error with arguments: -rs [nbEval]"<<std::endl; }
    }

    //RandomWalk
    if(std::string(argv[2]) == "-rw"){
        if(argc == 3) {
            RandomWalk rw(ks);
            rw.run(sol);
            rw.exportNeighborhoodToCsv();
        }
        else{ std::cout<<"error with arguments: -rw"<<std::endl; }
    }

    //HillClimber
    if(std::string(argv[2]) == "-hc") {
        if(argc == 5) {
            HillClimber hc(ks,std::stoi(argv[3]),std::stoi(argv[4]));
            hc.run(sol);
            std::string imp = std::stoi(argv[4]) == 0 ? "best improvement: " : "first improvement: ";
            std::cout <<imp<< sol.fitness() << std::endl;
        }
        else { std::cout<<"error with arguments: -hc [nbEval] [improvement: 0=best, 1=first]"<<std::endl; }
    }

    //SimulatedAnnealing
    if(std::string(argv[2]) == "-sa") {
        if(argc == 6) {
            SimulatedAnnealing sa(ks, std::stoi(argv[3]), std::stoi(argv[4]), std::stof(argv[5]));
            sa.run(sol);
            std::cout << argv[3] << "\t" << sol.fitness() << std::endl;
        }
        else { std::cout<<"error with arguments: -sa [nbEval] [initTemperature] [alpha]"<<std::endl; }
    }

    return 0;
}
