#include "CacheSimulator.cpp"
#include <iostream>
#include <conio.h>
using namespace std;

string TRACE_FILE = "swim.trace"; // CAN CHANGE THIS NAME TO ANY TRACE FILE IN ../TRACES/
string RELATIVE_PATH = "./traces/";

int main()
{
	int setcount, blockcount, blocksize;
	string replacementpolicy, type;
	cout << "Enter number of sets" << endl;
	cin >> setcount;
	cout << "Enter number of blocks per set" << endl;
	cin >> blockcount;
	cout << "Enter size of block in bytes" << endl;
	cin >> blocksize;
	cout << "Enter replacement policy (FIFO or LRU)" << endl;
	cin >> replacementpolicy;
	cout << endl;


	CacheSimulator cachesim(RELATIVE_PATH + TRACE_FILE, setcount, blockcount, blocksize, replacementpolicy);
	cout << endl;

	auto stats = cachesim.GetSummaryStats();
	if (setcount != 1 && blockcount != 1)
		type = to_string(blockcount) + "-way Set Associative";
	else if (setcount == 1)
		type = "Fully Associative";
	else
		type = "Direct Mapped";

	cout << "====Cache Properties====" << endl;
	cout << "Cache size: " << (setcount * blockcount * blocksize) << " KB" << endl;
	cout << "Cache type: " << type << endl;
	cout << "Replacement policy: " << replacementpolicy << endl;
	cout << endl;
	cout << "====Cache Simulation Statistics====" << endl;
	cout << "Access count: " << stats.second << endl;
	cout << "Hit count: " << stats.first << endl;
	cout << "Hit rate: " << 100 * (float)stats.first / (float)stats.second << "%" << endl;

	cout << "\nPress any key to exit..." << endl;
	_getch();
	return 0;
}