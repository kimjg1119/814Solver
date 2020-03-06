#include "programhandler.h"

ProgramHandler::ProgramHandler(int _sz, string _pV, string _pT) :
	programVersion(_pV), programTitle(_pT), man(_sz, (int)time(NULL)), bf(0), timeSum(0) {
	bf = clock();
	cout << fixed;
	cout.precision(2);
}

void ProgramHandler::PrintIntro() {
	cout << "이 프로그램은 현재 버전 " << programVersion << "입니다." << endl;
	cout << "이 버전을 요약하면 다음과 같습니다: " << programTitle << endl;
	cout << "프로그램을 실행하기 전에 반드시 상수 설정에 주의하십시오." << endl;
	cout << endl;
}

void ProgramHandler::Save() {
	cout << "Saving...";
	const string fileOpenString = saveFileName;
	ofstream out(fileOpenString);
	out << programVersion << endl << nowEpoch << endl;
	man.SaveAllGene(out);
	cout << " Saved." << endl;
}

void ProgramHandler::SaveLoadManage() {

	string tempFileName, sel;
	while (true) {
		cout << "로드할 파일이 있으십니까? (Y/N) : ";
		cin >> sel;
		if ((int)sel.length() != 1) cout << "다시 입력해 주세요." << endl;
		else if (sel[0] != 'Y' && sel[0] != 'N') cout << "다시 입력해 주세요." << endl;
		else break;
	}
	if (sel[0] == 'Y') {
		cout << "파일 이름을 입력해주세요: ";
		cin >> tempFileName;
		const string cFileName = tempFileName;
		ifstream in(cFileName);

		string loadVer;
		int loadEpoch;
		in >> loadVer >> loadEpoch;
		if (loadVer != programVersion) {
			while (true) {
				cout << "버전이 일치하지 않습니다. 계속하시겠습니까? (Y/N) :";
				cin >> sel;
				if ((int)sel.length() != 1) cout << "다시 입력해 주세요." << endl;
				else if (sel[0] != 'Y' && sel[0] != 'N') cout << "다시 입력해 주세요." << endl;
				else break;
			}
			if (sel[0] == 'N') exit(0);
		}
		nowEpoch = loadEpoch;

		man.LoadAllGene(in);
		cout << "로딩되었습니다." << endl << endl;
	}
	cout << endl;


	cout << "세이브할 파일 이름을 입력하세요: ";
	cin >> saveFileName;
	cout << "세이브 주기를 입력하세요: ";
	cin >> saveInterval;
	cout << endl;
}

void ProgramHandler::PrintBestGene() {
	cout << "Best gene: " << endl;
	man.PrintBestGene();
	cout << endl;
}

void ProgramHandler::PrintTop10() {
	vector<int> topScoreVec = man.top10Score();
	cout << "Top 10 Gene Scores: ";
	for (int hrScore : topScoreVec)
		cout << hrScore << " ";
	cout << endl;
}

void ProgramHandler::PrintAverage() {
	cout << "Average Score: " << man.returnAverageScore() << endl;
}

void ProgramHandler::NextEpoch() {
	man.NextGeneration();
	nowEpoch++;
	cout << "Epoch: " << nowEpoch;
	cout << " Best Score: " << man.BestGeneScore();

	clock_t nowTime = clock();
	cout << " Time: " << (double)(nowTime - bf) / CLOCKS_PER_SEC << "s" << endl;
	timeSum += (nowTime - bf);
	bf = nowTime;
}

void ProgramHandler::Visualizing() {
	cout << endl << "<Visualizing>" << endl << endl;
	PrintBestGene();
	PrintTop10();
	PrintAverage();
	cout << "Time Average: " << ((double)timeSum / (double)visualInterval) / CLOCKS_PER_SEC << "s" << endl;
	timeSum = 0;
	cout << endl;
}

void ProgramHandler::Run() {
	PrintIntro();
	SaveLoadManage();
	cout << endl << "Running..." << endl << endl;
	while (true) {
		NextEpoch();
		if (nowEpoch % visualInterval == 0)
			Visualizing();
		if (nowEpoch % saveInterval == 0)
			Save();
	}
}