#!/bin/bash

#filename of the knapsack instance
filename=ks_1000.dat

nbRun=100

nbEvalList="10 50 100 500 1000 2000 5000 10000 50000 100000"

echo random search

echo nbeval fitness > rs.csv
for n in ${nbEvalList}
do
	echo nbEval ${n}
	for((i=0; i < ${nbRun}; i++))
	do
		echo -n $i' '
		./build/main.out ${filename} -rs ${n} >> rs.csv
	done
	echo
done
echo

echo random walk of 1000 steps

echo fitness > rs.csv
