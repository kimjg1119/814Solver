#include <bits/stdc++.h>
#include "genealgomanager.h"

using namespace std;

int main() {
	int seed = (unsigned int)time(NULL);
	GeneAlgoManager GA(100, seed);
	clock_t bf = clock(), timeSum = 0;

	//GA.LoadAllGene();
	for (int i = 0; i < 10000; i++) {
		GA.NextGeneration();
		clock_t now_time = clock();
		cout << "Epoch: " << i << ", Score: " << GA.BestGeneScore() << ", Time: " << (now_time - bf) / CLOCKS_PER_SEC << "s" << endl;
		timeSum += now_time - bf;
		bf = now_time;

		if (i % 10 == 0) {
			cout << "Best Gene:" << endl;
			GA.PrintBestGene();
			cout << "Average Time: " << (double)(timeSum / CLOCKS_PER_SEC) / 10 << "s" << endl;
			timeSum = 0;
			GA.SaveAllGene();
		}
	}
	GA.PrintBestGene();
	return 0;
}