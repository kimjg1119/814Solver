#include "gene.h"
#include <cstring>

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

void Gene::ClearChk() { memset(chk, 0, sizeof chk); }
void Gene::ClearChk(int i, int j) { chk[i][j] = 0; }
void Gene::SetChk(int i, int j) { chk[i][j] = 1; }
int Gene::GetChk(int i, int j) { return chk[i][j]; }