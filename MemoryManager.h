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
	HWND getHWND();
	DWORD getPID();
	DWORD getBaseAddress();
	HANDLE MemoryManager::getPhandle();
};
