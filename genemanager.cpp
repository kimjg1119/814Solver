#include "genemanager.h"
#include "randommanager.h"
#include <iostream>

using namespace std;
typedef tuple<int, int, int, int> tp;


int GeneManager::EvaluateMax(Gene &hGene) {
	return eval(hGene);
}

int GeneManager::EvaluateIgnoreOne(Gene&){
	// here!
}

void GeneManager::ProbMutate(Gene &hGene, double prob, RandomManager &rm) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++) {
			if (rm.RandomDouble01() <= prob)
				hGene.ModifyGene(i, j, rm.RandomInt09());
		}
	}
}

#include <iostream>

void GeneManager::Optimizer(Gene& g, int max_iter) {
	int flag = 1;
	for (int iter = 0; iter < max_iter && flag; iter++) {
		flag = 0;
		int now = EvaluateMax(g);
		//cout << now << endl;
		int tmp = now + 1;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 14; j++) {
				tmp = now + 1;
				while (tmp) {
					int prv = g.GetGene(i, j);
					g.ModifyGene(i, j, tmp % 10); tmp /= 10;
					int nxt = EvaluateMax(g);
					if (now >= nxt) g.ModifyGene(i, j, prv);
					else now = nxt, flag = 1;
				}
				if (flag) break;
			}
			if (flag) break;
		}
	}
}

void GeneManager::Shuffle(Gene &g) {
	for (int k = 0; k < 500; k++) {
		Pos a = rm.RandomPosition();
		Pos b = rm.RandomPosition();

		int bb = g.GetGene(a.x, a.y);
		int aa = g.GetGene(b.x, b.y);
		g.ModifyGene(a.x, a.y, aa);
		g.ModifyGene(b.x, b.y, bb);
	}
}

bool GeneManager::_eval(const int v[8][14], int i, int j, int now) {
	if (!now) return 1;
	for (int k = 0; k<8; k++) {
		int ii = i + dx[k];
		int jj = j + dy[k];
		if (ii < 0 || jj < 0 || ii >= 8 || jj >= 14) continue;
		if (v[ii][jj] == now % 10) {
			if (_eval(v, ii, jj, now / 10)) return 1;
		}
	}
	return 0;
}

bool GeneManager::_eval(const int v[8][14], int now) {
	for (int i = 0; i<8; i++) for (int j = 0; j<14; j++) {
		if (v[i][j] == now % 10) {
			if (_eval(v, i, j, now / 10)) return 1;
		}
	}
	return 0;
}

int GeneManager::eval(const int v[8][14]) {
	for (int t = 1; ; t++) {
		if (!_eval(v, t)) return t - 1;
	}
}

int GeneManager::eval(Gene &g) {
	int v[8][14];
	g.GetGene(v);
	return eval(v);
}