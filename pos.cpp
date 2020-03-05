#include "pos.h"

Pos::Pos(int _x = 0, int _y = 0) : x(_x), y(_y) {}

bool Pos::operator==(Pos &p){
	if (x == p.x && y == p.y) return true;
	return false;
}