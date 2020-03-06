#include "EvalManager.h"

bool EvalManager::BackTracking(const int v[8][14], int i, int j, int now) {
	if (!now) return 1;
	for (int k = 0; k<8; k++) {
		int ii = i + dx[k];
		int jj = j + dy[k];
		if (ii < 0 || jj < 0 || ii >= 8 || jj >= 14) continue;
		if (v[ii][jj] == now % 10) {
			if (BackTracking(v, ii, jj, now / 10)) return 1;
		}
	}
	return 0;
}

bool EvalManager::HasNum(const int v[8][14], int now) {
	for (int i = 0; i<8; i++) for (int j = 0; j<14; j++) {
		if (v[i][j] == now % 10) {
			if (BackTracking(v, i, j, now / 10)) return 1;
		}
	}
	return 0;
}

int EvalManager::GetScore(const int v[8][14]) {
	for (int t = 1; ; t++) {
		if (!HasNum(v, t)) return t - 1;
	}
}

double EvalManager::GetScoreIgnoreOne(const int v[8][14]) {
	double ret = 0;
	double step = 1;
	for (int t = 1; t <= ignore_limit; t++) {
		if (HasNum(v, t)) ret += step;
		else step /= 2;
	}
	return ret;
}

int EvalManager::EvalScore(Gene &g) {
	int v[8][14];
	g.GetGene(v);
	return GetScore(v);
}

double EvalManager::EvalIgnoreOne(Gene &g) {
	int v[8][14];
	g.GetGene(v);
	return GetScoreIgnoreOne(v);
}