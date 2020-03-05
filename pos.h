#ifndef __pos_h__
#define __pos_h__

class Pos {
public:
	int x, y;
	Pos(int, int);
	bool operator==(Pos&);
};

#endif __pos_h__
