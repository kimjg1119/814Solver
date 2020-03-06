#ifndef __programhandler_h__
#define __programhandler_h__

#include <bits/stdc++.h>
#include "genealgomanager.h"

using namespace std;

#include <bits/stdc++.h>

class ProgramHandler {
private:

	const int visualInterval = 10;

	GeneAlgoManager man;
	string programVersion;
	string programTitle;
	string saveFileName;
	int saveInterval = 5;
	int nowEpoch = 0;
	time_t bf, timeSum;

	void PrintIntro();
	void Save();
	void SaveLoadManage();
	void PrintBestGene();
	void PrintTop10();
	void PrintAverage();
	void NextEpoch();
	void Visualizing();
public:
	ProgramHandler(int, string, string);
	void Run();
};

#endif __programhandler_h__