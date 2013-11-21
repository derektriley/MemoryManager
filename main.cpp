#include <iostream>
#include "MemoryManager.h"
#include <stdio.h>
#include <tchar.h>

using namespace std;

int main(int argc, char **argv) 
{
	cout << "Minesweeper hack.\n";
	MemoryManager mine(_T("Minesweeper"), _T("minesweeper.exe"));
	cout << "\nAttached.\n";
	cout << "Base address: 0x" << hex << mine.getBaseAddress() << endl;
	cout << "PID: " << dec << mine.getPID() << endl;
	cout << "Number of Mines: " << mine.readMines() << endl;
	cout << "Setting mines to zero" << endl;
	mine.writeMines(0);
	for(int i=0;i<4;i++) {
		cout << ".";
		Sleep(1000);
	}
	cout << endl;
	return 0;
}