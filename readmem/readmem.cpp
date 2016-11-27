#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

/**
* This program gets a process handle to "Minesweeper"
* it then prints out the value at "address" every half second
* using ReadProcessMemory
* This value is simply the current number of mines on the level
*/
int main()
{
	// Offsets
	DWORD dwImageBase = 0x400000;
	DWORD dwVirtualAddress = 0x00001000;
	DWORD dwBaseAddress = 0x000111;
	//DWORD dwOldWorldBase = 0x103BBA8;
	DWORD pWorldBase = 0x103ABF0;
	//WORD wOldPlayerOffset = 0x1650;
	WORD wPlayerOffset = 0x1658;
	BYTE bVstateOffset = 0x34;

	// Number of bytes read by RPM
	DWORD dwBytesRead = 0;
	HWND hwnd;
	hwnd = FindWindow(NULL, L"DayZ");

	// The process ID, used to r/w into the memory
	DWORD pid;
	// Get the process ID and place the value at the address of pid
	GetWindowThreadProcessId(hwnd, &pid);
	cout << "pid = " << pid << "\n";

	// Open a handle to the process specified by pid
	HANDLE phandle;
	// exit if OpenProcess returns NULL
	if (!(phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid)))
	{
		cout << "ERROR: Could not get process handle, OpenProcess returned error\n";
		return 0;
	}

	
	// Follow the pointer value to the player table
	DWORD dwAddr1;
	DWORD dwAddr2;
	DWORD dwAddr3;
	dwAddr1 = ReadProcessMemory(phandle, (LPCVOID)(dwImageBase + pWorldBase), &dwAddr1, sizeof(int), &dwBytesRead);

	printf("Read %d bytes\n", dwBytesRead);
	printf("Initial Value: %010X\n", dwAddr1);

	dwAddr2 = ReadProcessMemory(phandle, (LPCVOID)(dwAddr1 + wPlayerOffset), &dwAddr2, sizeof(int), &dwBytesRead);

	printf("Read %d bytes\n", dwBytesRead);
	printf("Second Value: %010X\n", dwAddr2);

	// Read forever until program closes
	while (1)
	{
		// Read the memory at the specified address, store it at &values
		//ReadProcessMemory(phandle, (void*)dwPtrBaseAddress+dwWorldBase, &value, sizeof(int), &dwPtrBytesRead);
		dwAddr3 = ReadProcessMemory(phandle, (LPCVOID)(dwAddr2 + bVstateOffset), &dwAddr3, sizeof(int), &dwBytesRead);

		printf("Read %d bytes\n", dwBytesRead);
		printf("Value: %010X\n", dwAddr3);

		Sleep(1000);
	}
	return 0;
}






