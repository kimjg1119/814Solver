#ifndef __randommanager_h__
#define __randommanager_h__

#include <random>
#include <ctime>
#include "pos.h"
using namespace std;

class RandomManager {
private:
	mt19937_64 seed;
	uniform_int_distribution<int> rngInt09;
	uniform_real_distribution<double> rngDouble01;

public:
	RandomManager(unsigned int);
	int RandomInt09();
	double RandomDouble01();
	double RandomDouble(double);
	Pos RandomPosition();
	pair<Pos,Pos> TwoRandomPosition();
};

#endif __randommanager_h__