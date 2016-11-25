// readmem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

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
	// The address we want to read from
	//DWORD address = 0x100579C;
	DWORD address = 0x01F4C380;
	// Store the value we are reading
	int value = 0;
	// The process ID, used to r/w into the memory
	DWORD pid;
	// A Handle to the window
	HWND hwnd;

	hwnd = FindWindow(NULL, L"Minesweeper");
	

	// If FindWindow is NULL, exit
	if (!hwnd)
	{
		cout << "Window not found, FindWindow returned NULL\n";
		return 0;
	}

	// Get the process ID and place the value at the address of pid
	GetWindowThreadProcessId(hwnd, &pid);
	// Open a handle to the process specified by pid
	HANDLE phandle = OpenProcess(PROCESS_VM_READ, 0, pid);
	// exit if OpenProcess returns NULL
	if (!phandle)
	{
		cout << "Could not get process handle, OpenProcess returned error\n";
		return 0;
	}

	// Read forever until program closes
	while (1)
	{
		ReadProcessMemory(phandle, (void*)address, &value, sizeof(value), 0);
		cout << value << "\n";
		Sleep(500);
	}
	
    return 0;
}

