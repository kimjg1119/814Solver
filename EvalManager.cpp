#include "EvalManager.h"

bool EvalManager::BackTracking(Gene& g, int i, int j, int now, int flag) {
	if (!now) {
		if (flag) g.SetChk(i, j);
		return 1;
	}
	for (int k = 0; k<8; k++) {
		int ii = i + dx[k];
		int jj = j + dy[k];
		if (ii < 0 || jj < 0 || ii >= 8 || jj >= 14) continue;
		if (g.GetGene(ii, jj) == now % 10) {
			if (BackTracking(g, ii, jj, now / 10, flag)) {
				if(flag) g.SetChk(i, j);
				return 1;
			}
		}
	}
	return 0;
}

bool EvalManager::HasNum(Gene& g, int now, int flag) {
	for (int i = 0; i<8; i++) for (int j = 0; j<14; j++) {
		if (g.GetGene(i, j) == now % 10) {
			if (BackTracking(g, i, j, now / 10, flag)) return 1;
		}
	}
	return 0;
}

int EvalManager::GetScore(Gene& g) {
	for (int t = 1; ; t++) {
		if (!HasNum(g, t, 1)) return t - 1;
	}
}

double EvalManager::GetScoreIgnoreOne(Gene& g) {
	double ret = 0;
	double step = 1;
	for (int t = 1; t <= ignore_limit; t++) {
		if (HasNum(g, t, 0)) ret += step;
		else step /= 2;
	}
	return ret;
}

int EvalManager::EvalScore(Gene &g) {
	return GetScore(g);
}

double EvalManager::EvalIgnoreOne(Gene &g) {
	return GetScoreIgnoreOne(g);
}