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
	RandomManager rm;

	bool _eval(const int v[8][14], int i, int j, int now);
	bool _eval(const int v[8][14], int now);
	int eval(const int v[8][14]);
	int eval(Gene&);

public:
	GeneManager(int seed) : rm(seed) {}
	int EvaluateMax(Gene&);
	int EvaluateIgnoreOne(Gene&);
	void ProbMutate(Gene&, double, RandomManager&);
	void Optimizer(Gene&, int);
	void Shuffle(Gene&);
};

#endif __genemanager_h__