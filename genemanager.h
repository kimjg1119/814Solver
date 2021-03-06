#ifndef __genemanager_h__
#define __genemanager_h__

#include "gene.h"
#include "EvalManager.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <queue>

using namespace std;

class GeneManager {
private:
	const int dx[8] = { 1,0,-1,0,1,1,-1,-1 };
	const int dy[8] = { 0,1,0,-1,1,-1,1,-1 };
	RandomManager rm;
	EvalManager eval;

public:
	GeneManager(int seed) : rm(seed) {}
	int EvaluateMax(Gene&);
	double EvaluateIgnoreOne(Gene&);
	void ProbMutate(Gene&, double, RandomManager&);
	void Optimizer(Gene&, int, int);
	void Shuffle(Gene&);

	
};

#endif __genemanager_h__