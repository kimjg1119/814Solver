#ifndef __genemanager_h__
#define __genemanager_h__

#include "gene.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <queue>

using namespace std;

class GeneManager {
private:
	int dx[8] = { 1,0,-1,0,1,1,-1,-1 };
	int dy[8] = { 0,1,0,-1,1,-1,1,-1 };
	vector<int> BasicEvaluate(Gene&);

public:
	int EvaluateMax(Gene&);
	void ProbMutate(Gene&, double, RandomManager&);
	void Optimizer(Gene&, int);
};

#endif __genemanager_h__