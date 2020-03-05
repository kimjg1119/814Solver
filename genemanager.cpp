#include "genemanager.h"
#include "randommanager.h"

using namespace std;
typedef tuple<int, int, int, int> tp;

vector<int> GeneManager::BasicEvaluate(Gene &hGene) {
	int hArr[8][14]; 
	hGene.GetGene(hArr);
	vector<int> chk(10000);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++) {
			queue<tp> Q;
			Q.emplace(i, j, hArr[i][j], 1);
			chk[hArr[i][j]] = 1;

			while (!Q.empty()) {
				int hx, hy, val, idx;
				tie(hx, hy, val, idx) = Q.front(); Q.pop();

				for (int k = 0; k < 8; k++) {
					int nx = hx + dx[k], ny = hy + dy[k];
					if (nx < 0 || nx >= 8 || ny < 0 || ny >= 14) continue;

					int nval = val * 10 + hArr[nx][ny];
					chk[nval] = 1;

					if (idx == 3) continue;
					Q.emplace(nx, ny, val * 10 + hArr[nx][ny], idx + 1);
				}
			}
		}
	}

	return chk;
}

int GeneManager::EvaluateMax(Gene &hGene) {
	vector<int> chk = BasicEvaluate(hGene);
	for (int i = 1; i < chk.size(); i++) {
		if (!chk[i]) return i - 1;
	}
	return 20000;
}

void GeneManager::ProbMutate(Gene &hGene, double prob, RandomManager &rm) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++) {
			if (rm.RandomDouble01() <= prob)
				hGene.ModifyGene(i, j, rm.RandomInt09());
		}
	}
}