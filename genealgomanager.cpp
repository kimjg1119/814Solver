#include "genealgomanager.h"

GeneAlgoManager::GeneAlgoManager(int _n, int seed)
	: n(_n), geneScore(_n), geneFitScore(_n), geneFitness(_n), fitSum(0), rm(seed), gm(seed) {
	for (int i = 0; i < _n; i++) {
		Gene tempGene(rm);
		geneArr.push_back(tempGene);
	}
}

void GeneAlgoManager::CalculateScore() {
	for (int i = 0; i < n; i++) {
		geneScore[i] = gm.EvaluateMax(geneArr[i]);
		geneFitScore[i] = gm.EvaluateIgnoreOne(geneArr[i]);
	}
}

double GeneAlgoManager::CalculateFitness() {
	double fitSum = 0;
	double maxScore = *max_element(geneFitScore.begin(), geneFitScore.end());
	double minScore = *min_element(geneFitScore.begin(), geneFitScore.end());
	for (int i = 0; i < n; i++) {
		geneFitness[i] = (geneFitScore[i] - minScore) + (maxScore - minScore) / (fitness_k - 1);
		fitSum += geneFitness[i];
	}
	return fitSum;
}

int GeneAlgoManager::SelectParent(double fitSum) {
	double pt = rm.RandomDouble(fitSum);
	double timeSum = 0;
	int sel = -1;
	for (int i = 0; i < n; i++) {
		timeSum += geneFitness[i];
		if (pt <= timeSum) {
			sel = i;
			break;
		}
	}
	if (sel == -1) return n - 1;
	else return sel;
}

void GeneAlgoManager::IndividualCross(Gene& parGeneA, Gene& parGeneB, Gene& childGene) {
	int parA[8][14], parB[8][14], child[8][14];
	parGeneA.GetGene(parA);
	parGeneB.GetGene(parB);
	childGene.GetGene(child);

	pair<Pos, Pos> cr_pos = rm.TwoRandomPosition();
	Pos posA = cr_pos.first, posB = cr_pos.second;
	if (posA.x > posB.x) swap(posA, posB);
	if (posA.y > posB.y) swap(posA.y, posB.y);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 14; j++)
			child[i][j] = parA[i][j];
	for (int i = posA.x; i < posB.x; i++)
		for (int j = posA.y; j < posB.y; j++)
			child[i][j] = parB[i][j];

	childGene.InitGene(child);
}

void GeneAlgoManager::Cross() { //need optimization

	vector<Gene> newGene(n);
	int parA = SelectParent(fitSum);
	int parB = SelectParent(fitSum);

	typedef pair<int, int> pii;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 0; i < n; i++) {
		pq.emplace(geneFitScore[i], i);
		while (pq.size() > elite) pq.pop();
	}
	for (int i = 0; i < elite; i++) {
		int idx = pq.top().second;
		pq.pop();
		newGene[i] = geneArr[idx];
	}

	for (int i = elite; i < n; i++) {
		if (parA == parB) {
			newGene[i] = geneArr[parA];
			continue;
		}

		IndividualCross(geneArr[parA], geneArr[parB], newGene[i]);

		parA = SelectParent(fitSum);
		parB = SelectParent(fitSum);
	}

	geneArr = newGene;
}

void GeneAlgoManager::Mutate() {
	for (int i = 0; i < n; i++) {
		if (rm.RandomDouble01() < all_init) {
			Gene newGene(rm);
			geneArr[i] = newGene;
		}
		if (rm.RandomDouble01() < gene_mutate_prob)
			gm.ProbMutate(geneArr[i], mutate_prob, rm);
	}
}

void GeneAlgoManager::Optimize() {
	for (int i = 0; i < n; i++) {
		if (rm.RandomDouble(10.0) <= 1) gm.Optimizer(geneArr[i], max_iter, 1);
		else gm.Optimizer(geneArr[i], max_iter, 0);
	}
		
}
void GeneAlgoManager::SaveBestGene() {
	int ma = -1, mai = -1;
	for (int i = 0; i < n; i++) {
		if (geneScore[i] > ma) {
			ma = geneScore[i];
			mai = i;
		}
	}
	if (ma < gm.EvaluateMax(bestGene)) return;
	bestGene = geneArr[mai];
}

void GeneAlgoManager::NextGeneration()
{
	CalculateScore();
	SaveBestGene();
	fitSum = CalculateFitness();
	Cross();
	Mutate();
	Optimize();
}

void GeneAlgoManager::PrintBestGene() {
	int hGene[8][14];
	bestGene.GetGene(hGene);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++)
			cout << hGene[i][j];
		cout << endl;
	}
}

void GeneAlgoManager::SaveAllGene(ofstream& out) {
	int hGene[8][14];
	for (int t = 0; t < n; t++) {
		geneArr[t].GetGene(hGene);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 14; j++)
				out << hGene[i][j];
			out << endl;
		}
	}
}

void GeneAlgoManager::LoadAllGene(ifstream& in) {
	int hGene[8][14];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 8; j++) {
			string s; in >> s;
			for (int k = 0; k < 14; k++)
				hGene[j][k] = s[k] - '0';
		}
		geneArr[i].InitGene(hGene);
	}
}


int GeneAlgoManager::BestGeneScore() {
	return gm.EvaluateMax(bestGene);
}

double GeneAlgoManager::returnAverageScore(){
	double timeSum = 0;
	for (int i = 0; i < n; i++) {
		timeSum += geneScore[i];
	}
	return timeSum / n;
}

vector<int> GeneAlgoManager::top10Score() {
	vector<int> compareVec = geneScore;
	sort(compareVec.begin(), compareVec.end(), greater<int>());
	vector<int> returnVec(10);
	for (int i = 0; i < 10; i++) returnVec[i] = compareVec[i];
	return returnVec;
}