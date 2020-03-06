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
	const double gene_mutate_prob = 0.2;
	const double all_init = 0.07;
	const int elite = 10;
	const int max_iter = 10000;

	int n;
	double fitSum;
	Gene bestGene;
	vector<Gene> geneArr;
	vector<int> geneScore;
	vector<double> geneFitScore;
	vector<double> geneFitness;
	GeneManager gm;
	RandomManager rm;

	void CalculateScore();
	double CalculateFitness();
	int SelectParent(double);
	void IndividualCross(Gene&, Gene&, Gene&);
	void Cross();
	void Mutate();
	void Optimize();
	void SaveBestGene();

public:
	GeneAlgoManager(int, int);
	void NextGeneration();
	void PrintBestGene();
	int BestGeneScore();
	void SaveAllGene();
	void LoadAllGene();
	double returnAverageScore();
	vector<int> top10Score();
};

#endif __genealgomanager_h__