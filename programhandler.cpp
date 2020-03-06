#include "programhandler.h"

ProgramHandler::ProgramHandler(int _sz, string _pV, string _pT) :
	programVersion(_pV), programTitle(_pT), man(_sz, (int)time(NULL)), bf(0), timeSum(0) {
	bf = clock();
	cout << fixed;
	cout.precision(2);
}

void ProgramHandler::PrintIntro() {
	cout << "�� ���α׷��� ���� ���� " << programVersion << "�Դϴ�." << endl;
	cout << "�� ������ ����ϸ� ������ �����ϴ�: " << programTitle << endl;
	cout << "���α׷��� �����ϱ� ���� �ݵ�� ��� ������ �����Ͻʽÿ�." << endl;
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
		cout << "�ε��� ������ �����ʴϱ�? (Y/N) : ";
		cin >> sel;
		if ((int)sel.length() != 1) cout << "�ٽ� �Է��� �ּ���." << endl;
		else if (sel[0] != 'Y' && sel[0] != 'N') cout << "�ٽ� �Է��� �ּ���." << endl;
		else break;
	}
	if (sel[0] == 'Y') {
		cout << "���� �̸��� �Է����ּ���: ";
		cin >> tempFileName;
		const string cFileName = tempFileName;
		ifstream in(cFileName);

		string loadVer;
		int loadEpoch;
		in >> loadVer >> loadEpoch;
		if (loadVer != programVersion) {
			while (true) {
				cout << "������ ��ġ���� �ʽ��ϴ�. ����Ͻðڽ��ϱ�? (Y/N) :";
				cin >> sel;
				if ((int)sel.length() != 1) cout << "�ٽ� �Է��� �ּ���." << endl;
				else if (sel[0] != 'Y' && sel[0] != 'N') cout << "�ٽ� �Է��� �ּ���." << endl;
				else break;
			}
			if (sel[0] == 'N') exit(0);
		}
		nowEpoch = loadEpoch;

		man.LoadAllGene(in);
		cout << "�ε��Ǿ����ϴ�." << endl << endl;
	}
	cout << endl;


	cout << "���̺��� ���� �̸��� �Է��ϼ���: ";
	cin >> saveFileName;
	cout << "���̺� �ֱ⸦ �Է��ϼ���: ";
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