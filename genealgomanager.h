#ifndef __genealgomanager_h__
#define __genealgomanager_h__

#include "gene.h"
#include "genemanager.h"
#include <bits/stdc++.h>

using namespace std;

class GeneAlgoManager {
private:
	const double fitness_k = 3;
	const double mutate_prob = 0.01;
	const int remain = 25;
	const int elite = 5;

	int n;
	double fitSum;
	Gene bestGene;
	vector<Gene> geneArr;
	vector<int> geneScore;
	vector<double> geneFitness;
	GeneManager gm;
	RandomManager rm;

	void CalculateScore();
	double CalculateFitness();
	int SelectParent(double);
	void IndividualCross(Gene&,Gene&,Gene&);
	void Cross();
	void Mutate();
	void SaveBestGene();

public:
	GeneAlgoManager(int, int);
	void NextGeneration();
	void PrintBestGene();
	int BestGeneScore();
	void SaveAllGene();
	void LoadAllGene();
};

#endif __genealgomanager_h__