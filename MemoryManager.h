#include <windows.h>

class MemoryManager {
private:
    HWND hwnd;
    DWORD pid;
    HANDLE phandle;
    DWORD baseAddress;

public:
    // Constructor Takes window name and obtains hwnd, pid, phandle, and baseAddress
    MemoryManager(CONST TCHAR* name, TCHAR* nameExe);

    int readInt(DWORD address);
	int MemoryManager::readMines();
	void MemoryManager::writeMines(int value);
	HWND getHWND();
	DWORD getPID();
	DWORD getBaseAddress();
};
