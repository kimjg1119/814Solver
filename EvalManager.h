#ifndef __eval_h__
#define __eval_h__

#include "gene.h"

class EvalManager {
private:
	const int dx[8] = { 1,0,-1,0,1,1,-1,-1 };
	const int dy[8] = { 0,1,0,-1,1,-1,1,-1 };
	const int ignore_limit = 5000;
	bool BackTracking(Gene& g, int i, int j, int now, int flag);
	int GetScore(Gene&);
	double GetScoreIgnoreOne(Gene&);

public:
	bool HasNum(Gene& g, int now, int flag);
	double EvalIgnoreOne(Gene&);
	int EvalScore(Gene&);
};

#endif __eval_h__