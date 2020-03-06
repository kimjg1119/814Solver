#ifndef __eval_h__
#define __eval_h__

#include "gene.h"

class EvalManager {
private:
	const int dx[8] = { 1,0,-1,0,1,1,-1,-1 };
	const int dy[8] = { 0,1,0,-1,1,-1,1,-1 };
	const int ignore_limit = 5000;
	bool BackTracking(const int v[8][14], int i, int j, int now);
	bool HasNum(const int v[8][14], int now);
	int GetScore(const int v[8][14]);
	double GetScoreIgnoreOne(const int v[8][14]);

public:
	double EvalIgnoreOne(Gene&);
	int EvalScore(Gene&);
};

#endif __eval_h__