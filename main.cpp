#include <bits/stdc++.h>
#include "genealgomanager.h"

using namespace std;

int main() {
	int seed = (unsigned int)time(NULL);
	GeneAlgoManager GA(100, seed);

	//GA.LoadAllGene();
	for (int i = 0; i < 10000; i++) {
		GA.NextGeneration();
		if (i % 10 != 0) {
			cout << i << "\n";
			continue;
		}
		cout << "Epoch: " << i << ", Score: " << GA.BestGeneScore() << endl;
		GA.PrintBestGene();
		if (i % 1000 != 0) continue;
		GA.SaveAllGene();
	} 
	GA.PrintBestGene();
	return 0;
}