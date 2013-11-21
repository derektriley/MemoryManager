#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "MineSweeperMemory.h"

using namespace std;

int main(int argc, char **argv) 
{
	MineSweeperMemory mine;
	cout << "Minesweeper hack.\n";
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