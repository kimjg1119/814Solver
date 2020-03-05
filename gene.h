#ifndef __gene_h__
#define __gene_h__
#include "randommanager.h"

class Gene {
private:
	int gene[8][14] = {};
public :
	Gene();
	Gene(RandomManager&);
	void GetGene(int[8][14]);
	void initGene(int[8][14]);
	void ModifyGene(int, int, int);
};

#endif __gene_h__

