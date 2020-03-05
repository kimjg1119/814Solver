#include "randommanager.h"

using namespace std;

RandomManager::RandomManager(unsigned int basic_seed) : 
	seed(basic_seed), rngInt09(0,9), rngDouble01(0,1) {}

int RandomManager::RandomInt09(){
	return rngInt09(seed);
}

double RandomManager::RandomDouble01() {
	return rngDouble01(seed);
}

double RandomManager::RandomDouble(double lim) {
	uniform_real_distribution<double> rngDouble(0,lim);
	return rngDouble(seed);
}

Pos RandomManager::RandomPosition(){
	uniform_int_distribution<int> rng_x(0, 7);
	uniform_int_distribution<int> rng_y(0, 13);
	int pos_x = rng_x(seed);
	int pos_y = rng_y(seed);
	return Pos(pos_x, pos_y);
}

pair<Pos, Pos> RandomManager::TwoRandomPosition(){
	Pos first_pos = RandomPosition();
	while (true) {
		Pos second_pos = RandomPosition();
		if (first_pos == second_pos) continue;
		return make_pair(first_pos, second_pos);
	}
}