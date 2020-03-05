#include "gene.h"

Gene::Gene() {}

Gene::Gene(RandomManager &rm) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 14; j++)
			gene[i][j] = rm.RandomInt09();
}

void Gene::GetGene(int hGene[8][14]) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 14; j++)
			hGene[i][j] = gene[i][j];
}

int Gene::GetGene(int i, int j) {
	return gene[i][j];
}

void Gene::InitGene(int hGene[8][14]) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 14; j++)
			gene[i][j] = hGene[i][j];
}

void Gene::ModifyGene(int px, int py, int val) {
	gene[px][py] = val;
}