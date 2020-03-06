#include "genemanager.h"
#include "randommanager.h"
#include <iostream>

using namespace std;
typedef tuple<int, int, int, int> tp;


int GeneManager::EvaluateMax(Gene &hGene) {
	hGene.ClearChk();
	return eval.EvalScore(hGene);
}

double GeneManager::EvaluateIgnoreOne(Gene &hGene) {
	return eval.EvalIgnoreOne(hGene);
}

void GeneManager::ProbMutate(Gene &hGene, double prob, RandomManager &rm) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++) {
			if (rm.RandomDouble01() <= prob)
				hGene.ModifyGene(i, j, rm.RandomInt09());
		}
	}
}

void GeneManager::Optimizer(Gene& g, int max_iter, int type) {
	int flag = 1;
	for (int iter = 0; iter < max_iter && flag; iter++) {
		if (type == 1) {
			flag = 0;
			int now = EvaluateMax(g);
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
		else {
			flag = 0;
			int now = EvaluateMax(g);
			int tmp = now + 1;
			for (int i = 0; i < 8; i++) for (int j = 0; j<14; j++) {
				if (flag) break;
				if (g.GetChk(i, j)) continue;
				tmp = now + 1;
				while (tmp) {
					int prv = g.GetGene(i, j);
					g.ModifyGene(i, j, tmp % 10); tmp /= 10;
					if (eval.HasNum(g, now + 1, 0)) {
						flag = 1; break;
					}
				}
			}
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