#include <fstream>
#include <iostream>
#include <sstream>

#include "Knapsack.hpp"

Knapsack::Knapsack(std::string filename){

    std::ifstream file;
    std::string profit_parsed, profit_input;
    std::string weight_parsed, weight_input;
    std::string number_object;
    std::string max_weight;

    file.open(filename, std::ios::in);

    if(file.is_open() == false) { std::cout<<"erreur ouverture fichier!"<<std::endl; }
    else{
        getline(file, number_object);
        getline(file, profit_input);
        getline(file, weight_input);
        getline(file, max_weight);

        std::stringstream profits(profit_input);
        std::stringstream weights(weight_input);

        for(int i = 0; i < stoi(number_object); i++){
            getline(profits, profit_parsed, ' ');
            getline(weights, weight_parsed, ' ');

            _sack.push_back(Stuff{stoi(profit_parsed), stoi(weight_parsed)});
        }

        _maxWeight = stoi(max_weight);
        _beta = 0;

        double beta;
        for(int i = 0; i < size(); i++){
            beta = profit(i) / (double)weight(i);
            if(_beta < beta) { _beta = beta; }
        }
    }

    file.close();
}

void Knapsack::print_sack(){
    std::cout<<"number of stuff : "<<_sack.size()<<std::endl;
    std::cout<<"weight max in the bag: "<<_maxWeight<<std::endl;
    std::cout<<"penality: "<<_beta<<std::endl;

    for(int i = 0; i < size(); i++){
        std::cout<<"("<<profit(i)<<", "<<weight(i)<<") "<<std::endl;
    }
}

int Knapsack::profit(int i) {return _sack[i]._profit; }
int Knapsack::weight(int i) {return _sack[i]._weight; }
int Knapsack::size(){ return (int)_sack.size(); }

void Knapsack::eval(Solution &sol){
    double P_x = 0;
    double W_x = 0;

    for(int i = 0; i < size(); i++){
        if(sol.x(i)) {
            P_x += profit(i);
            W_x += weight(i);
        }
    }

    if(W_x <= _maxWeight) {sol.fitness() = P_x;}
    else{ sol.fitness() = P_x - (_beta * (W_x - _maxWeight)); }
}

Knapsack::~Knapsack() {}
