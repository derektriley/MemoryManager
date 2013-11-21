/*
	Derek Riley
	MemoryManager for Reading and Writing to another processes memory
	Minesweeper functions for changing values
*/

#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "MemoryManager.h"
#include <tchar.h>
#include <strsafe.h>
#define TH32CS_SNAPNOHEAPS 0x40000000

using namespace std;

void printError( TCHAR* msg );

MemoryManager::MemoryManager(CONST TCHAR* name, TCHAR* nameExe) {
    hwnd = FindWindow(0, (LPCSTR) name);
    if (!hwnd) {
        cout << "Window not found." << endl;
    }
	else {
		cout << "Window found." << endl;
	}
    
    GetWindowThreadProcessId(hwnd, &pid);
    phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    if (!phandle) {
        cout << "Could not get handle.\n";
    }   
	else {
		cout << "Obtained phandle, pid is " << pid << endl;
	}
   
	HANDLE hModuleSnap;
	MODULEENTRY32 me32;
	//  Take a snapshot of all modules in the specified process. 
	  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPNOHEAPS, pid ); 
	  if( hModuleSnap == INVALID_HANDLE_VALUE ) 
	  { 
		printError( TEXT("CreateToolhelp32Snapshot (of modules)") ); 
	  } 
 
	//  Set the size of the structure before using it. 
	  me32.dwSize = sizeof( MODULEENTRY32 ); 
 
	//  Retrieve information about the first module, 
	//  and exit if unsuccessful 
	  if( !Module32First( hModuleSnap, &me32 ) ) 
	  { 
		printError( TEXT("Module32First") );  // Show cause of failure 
		CloseHandle( hModuleSnap );     // Must clean up the snapshot object! 
	  } 
 
	//  Now walk the module list of the process, 
	//  and display information about each module 
	  int i = 0;
	  do 
	  { 
		_tprintf( TEXT("\n\n     MODULE NAME:     %s"),             me32.szModule ); 
		_tprintf( TEXT("\n     executable     = %s"),             me32.szExePath ); 
		_tprintf( TEXT("\n     process ID     = 0x%08X"),         me32.th32ProcessID ); 
		_tprintf( TEXT("\n     ref count (g)  =     0x%04X"),     me32.GlblcntUsage ); 
		_tprintf( TEXT("\n     ref count (p)  =     0x%04X"),     me32.ProccntUsage ); 
		_tprintf( TEXT("\n     base address   = 0x%08X"), (DWORD) me32.modBaseAddr ); 
		_tprintf( TEXT("\n     base size      = %d"),             me32.modBaseSize ); 
 
		if(_tcscmp(me32.szModule, nameExe) == 0) 
        { 
            baseAddress = (DWORD)me32.modBaseAddr; 
            break; 
        } 
		if (i == 10) break;
		i++;
	  } while( Module32Next( hModuleSnap, &me32 ) ); 

		_tprintf( TEXT("\n"));
 
	//  Do not forget to clean up the snapshot object. 
	  CloseHandle( hModuleSnap ); 
}


int MemoryManager::readInt(DWORD address) {
    int result, rm;
	rm = ReadProcessMemory(phandle, (void *) address, &result, sizeof(int), 0);
	if (!rm) {
		cout << "ReadProcessMemory failed.\n";
	}
	return result;
}

int MemoryManager::readMines() {
	DWORD staticOffset = 0x000AAC18;
	DWORD offset0 = 0x70;
	DWORD offset1 = 0x0;
	DWORD offset2 = 0x38;
	DWORD offset3 = 0x8;
	DWORD result;
	int value;
	ReadProcessMemory(phandle, (void *) (baseAddress + staticOffset), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset0), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset1), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset2), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset3), &value, sizeof(int), 0);
	return value;
}

void MemoryManager::writeMines(int value) {
	DWORD staticOffset = 0x000AAC18;
	DWORD offset0 = 0x70;
	DWORD offset1 = 0x0;
	DWORD offset2 = 0x38;
	DWORD offset3 = 0x8;
	DWORD result;
	ReadProcessMemory(phandle, (void *) (baseAddress + staticOffset), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset0), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset1), &result, sizeof(DWORD), 0);
	ReadProcessMemory(phandle, (void *) (result + offset2), &result, sizeof(DWORD), 0);
	WriteProcessMemory(phandle, (void *) (result + offset3), &value, sizeof(int), 0);
}

HWND MemoryManager::getHWND()
{
	return hwnd;
}

DWORD MemoryManager::getPID() 
{
	return pid;
}

DWORD MemoryManager::getBaseAddress()
{
	return baseAddress;

}


void printError( TCHAR* msg )
{
  DWORD eNum;
  TCHAR sysMsg[256];
  TCHAR* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         sysMsg, 256, NULL );

  // Trim the end of the line and terminate it with a null
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );

  // Display the message
  _tprintf( TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg );
}
