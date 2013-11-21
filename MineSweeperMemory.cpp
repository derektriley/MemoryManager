#include "MineSweeperMemory.h"
#include <tchar.h>

MineSweeperMemory::MineSweeperMemory() 
	:MemoryManager(_T("MineSweeper"), _T("minesweeper.exe"))
{}

int MineSweeperMemory::readMines() {
	DWORD staticOffset = 0x000AAC18;
	DWORD offset0 = 0x70;
	DWORD offset1 = 0x0;
	DWORD offset2 = 0x38;
	DWORD offset3 = 0x8;
	DWORD result;
	int value;
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (MemoryManager::getBaseAddress() + staticOffset), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset0), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset1), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset2), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset3), &value, sizeof(int), 0);
	return value;
}

void MineSweeperMemory::writeMines(int value) {
	DWORD staticOffset = 0x000AAC18;
	DWORD offset0 = 0x70;
	DWORD offset1 = 0x0;
	DWORD offset2 = 0x38;
	DWORD offset3 = 0x8;
	DWORD result;
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (MemoryManager::getBaseAddress() + staticOffset), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset0), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset1), &result, sizeof(DWORD), 0);
	ReadProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset2), &result, sizeof(DWORD), 0);
	WriteProcessMemory(MemoryManager::getPhandle(), (void *) (result + offset3), &value, sizeof(int), 0);
}